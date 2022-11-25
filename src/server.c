/**
 * @author Andrej123456789 (Andrej Bartulin),nikhilroxtomar (Nikhil Tomar)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: server.c, C file for a server
 * CREDITS: https://github.com/nikhilroxtomar/Chatroom-in-C
*/

#include "include/server.h"

#include <stdarg.h>

static _Atomic unsigned int cli_count = 0;
static int uid = 10;

static cvector_vector_type(client_t *) clients;
static pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    client_t* cli;
    Network* network;
} Arg2;

/* Overwrites stdout */
void str_overwrite_stdout()
{
    printf("\r%s", "> ");
    fflush(stdout);
}

/** 
 * Removes last element from array if it is \n 
 * @param arr - array
 * @param length - length
*/
void str_trim_lf(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    { // trim \n
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

/**
 * Removes substring in passed string
 * @param str - string
 * @param sub - substring to be removed
*/
char *strremove(char *str, const char *sub) 
{
    size_t len = strlen(sub);
    if (len > 0) {
        char *p = str;
        while ((p = strstr(p, sub)) != NULL) {
            memmove(p, p + len, strlen(p + len) + 1);
        }
    }
    return str;
}


/** 
 * Prints address of client
 * @param addr - address of client
*/
void print_client_addr(struct sockaddr_in addr)
{
    printf("%d.%d.%d.%d",
           addr.sin_addr.s_addr & 0xff,
           (addr.sin_addr.s_addr & 0xff00) >> 8,
           (addr.sin_addr.s_addr & 0xff0000) >> 16,
           (addr.sin_addr.s_addr & 0xff000000) >> 24);
}

/** 
 * Adds clients to queue 
 * @param cl - client
*/
void queue_add(client_t *cl)
{
    pthread_mutex_lock(&clients_mutex);

    cvector_push_back(clients, cl);
    pthread_mutex_unlock(&clients_mutex);
}

/** 
 * Removes clients to queue
 * @param uid - id (position in vector) of client
*/
void queue_remove(int uid)
{
    pthread_mutex_lock(&clients_mutex);

    cvector_erase(clients, uid);
    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Send message to all clients except sender
 * @param s - string
 * @param uid - id (position in vector) of client
*/
void send_message(char *s, int uid)
{
    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < cvector_size(clients); ++i)
    {
        if (clients[i]->uid != uid)
        {
            if (write(clients[i]->sockfd, s, strlen(s)) < 0)
            {
                perror("ERROR: write to descriptor failed");
                break;
            }
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Sends message to all clients 
 * @param s - string
*/
void send_message_all(const char *s, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, s);
    vsnprintf(buf, sizeof(buf), s, args);
    buf[sizeof(buf) - 1] = 0;
    va_end(args);

    pthread_mutex_lock(&clients_mutex);

    for (int i = 0; i < cvector_size(clients); ++i)
    {
        if (write(clients[i]->sockfd, buf, strlen(buf)) < 0)
        {
            perror("ERROR: write to descriptor failed");
            break;
        }
    }

    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Sends message to specified client
 * @param id - client id, aka position in vector
 * @param s - string
*/
void send_message_to(int id, const char* s, ...)
{
    char buf[1024];
    va_list args;
    va_start(args, s);
    vsnprintf(buf, sizeof(buf), s, args);
    buf[sizeof(buf) - 1] = 0;
    va_end(args);

    pthread_mutex_lock(&clients_mutex);

    if (write(clients[id]->sockfd, buf, strlen(buf)) < 0)
    {
        perror("ERROR: write to descriptor failed");
    }

    pthread_mutex_unlock(&clients_mutex);
}

/**
 * Handles all communication with the client
 * @param arg - argument(s)
*/
void *handle_client(void *arg)
{
    char buff_out[BUFFER_SZ];
    char name[32];
    int leave_flag = 0;

    Arg2* actual_arg_2 = arg;

    cli_count++;
    client_t *cli = actual_arg_2->cli;

    // Name
    if (recv(cli->sockfd, name, 32, 0) <= 0 || strlen(name) < 2 || strlen(name) >= 32 - 1)
    {
        printf("Didn't enter the name.\n");
        leave_flag = 1;
    }
    else
    {
        strcpy(cli->name, name);
        sprintf(buff_out, "%s has joined\n", cli->name);
        printf("%s", buff_out);
        send_message(buff_out, cli->uid);
    }

    bzero(buff_out, BUFFER_SZ);

    while (1)
    {
        if (leave_flag)
        {
            break;
        }

        int receive = recv(cli->sockfd, buff_out, BUFFER_SZ, 0);
        if (receive > 0)
        {
            if (strlen(buff_out) > 0)
            {
                send_message(buff_out, cli->uid);

                str_trim_lf(buff_out, strlen(buff_out));
                printf("%s\n", buff_out);

                const char* sub = malloc(sizeof(char) * 1024);
                strcat(sub, cli->name);
                strcat(sub, ": ");

                printf("%s\n", strremove(buff_out, sub));
                free(sub);
            }
        }
        else if (receive == 0 || strcmp(buff_out, "exit") == 0)
        {
            sprintf(buff_out, "%s has left\n", cli->name);
            printf("%s", buff_out);
            send_message(buff_out, cli->uid);
            leave_flag = 1;
        }
        else
        {
            printf("ERROR: -1\n");
            leave_flag = 1;
        }

        bzero(buff_out, BUFFER_SZ);
    }

    /* Delete client from queue and yield thread */
    close(cli->sockfd);
    queue_remove(cli->uid);
    free(cli);
    cli_count--;
    pthread_detach(pthread_self());

    return NULL;
}

/**
 * Starts a server 
 * @param arg - argument(s)
*/
void* StartServer(void* arg)
{
    Arg* actual_arg = arg;

    char *ip = actual_arg->network->ip;
    int port = actual_arg->network->port;
    int option = 1;
    int listenfd = 0, connfd = 0;
    struct sockaddr_in serv_addr;
    struct sockaddr_in cli_addr;
    pthread_t tid;

    /* Socket settings */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(ip);
    serv_addr.sin_port = htons(port);

    /* Ignore pipe signals */
    signal(SIGPIPE, SIG_IGN);

    if (setsockopt(listenfd, SOL_SOCKET, (SO_REUSEPORT | SO_REUSEADDR), (char *)&option, sizeof(option)) < 0)
    {
        perror("ERROR: setsockopt failed");
        return EXIT_FAILURE;
    }

    /* Bind */
    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR: Socket binding failed");
        return EXIT_FAILURE;
    }

    /* Listen */
    if (listen(listenfd, 10) < 0)
    {
        perror("ERROR: Socket listening failed");
        return EXIT_FAILURE;
    }

    printf("Server created!\n");

    while (1)
    {
        socklen_t clilen = sizeof(cli_addr);
        connfd = accept(listenfd, (struct sockaddr *)&cli_addr, &clilen);

        /* Check if max clients is reached */
        if ((cli_count + 1) == 5000) /* 5000 is safe border, it can go further but i won't push it here, you can do it for yourself */
        {
            printf("Max clients reached. Rejected: ");
            print_client_addr(cli_addr);
            printf(":%d\n", cli_addr.sin_port);
            close(connfd);
            continue;
        }

        /* Client settings */
        client_t *cli = (client_t *)malloc(sizeof(client_t));
        cli->address = cli_addr;
        cli->sockfd = connfd;
        cli->uid = uid++;

        Arg2* arg2 = malloc(sizeof(Arg2));
        arg2->cli = cli;
        arg2->network;

        /* Add client to the queue and fork thread */
        queue_add(cli);
        pthread_create(&tid, NULL, &handle_client, (void *)arg2);

        /* Reduce CPU usage */
        sleep(1);
    }

    return EXIT_SUCCESS;
}
