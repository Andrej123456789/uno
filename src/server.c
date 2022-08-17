/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: server.c, C file for a server for C version
 * CREDITS: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
 * NOTE: I am going to use colors currently becuse this code is just for POSIX now
*/

#include "include/server.h"
#include "include/util.h"
#include "include/strings.h"

static Vec clients;

/**
 * Sending/receiving text to/from client
 * @param connfd - something important but currently idk what is that
*/
void SendReceive(int connfd)
{
    char buff[MAX];
    int n;

    for (;;)
    {
        bzero(buff, MAX);
   
        /* read the message from client and copy it in buffer */
        read(connfd, buff, sizeof(buff));
        printf(from_to_client_color, buff);

        bzero(buff, MAX);
        n = 0;
        /* copy server message in the buffer */
        while ((buff[n++] = getchar()) != '\n')
            ;
   
        /* and send that buffer to client */
        write(connfd, buff, sizeof(buff));
   
        if (strncmp("exit", buff, 4) == 0) 
        {
            printf(server_exiting_color);
            break;
        }

        else if (strncmp("all", buff, 3) == 0)
        {
            printf(special_function_all_color, clients.size);
            write(connfd, "\n", sizeof(buff));
        }
    }
}

/**
 * Start a server
*/
void StartServer()
{
    int client = 0;

    int sockfd, connfd, len;
    struct sockaddr_in servaddr, cli;

    InitArray(&clients, 1);
   
    /* Socket create and verification */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        printf(socket_creation_failed_color);
        exit(0);
    }

    else
    {
        printf(socket_creation_color);
    }

    bzero(&servaddr, sizeof(servaddr));
   
    /* Assign IP, PORT */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);
   
    /* Binding newly created socket to given IP and verification */
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) 
    {
        printf(socket_bind_failed_color);
        exit(0);
    }

    else
    {
        printf(socket_bind_color);
    }
   
    // Now server is ready to listen and verification
    if ((listen(sockfd, 5)) != 0) 
    {
        printf(listen_failed_color);
        exit(0);
    }

    else
    {
        printf(server_listen_color);
    }

    len = sizeof(cli);
   
    /* Accept the data packet from client and verification */
    connfd = accept(sockfd, (SA*)&cli, &len);
    if (connfd < 0) 
    {
        printf(failed_to_accept_client_color);
        exit(0);
    }

    else
    {
        printf(accept_client_color, client);
        InsertArray(&clients, client);
        client++;
    }
   
    SendReceive(connfd);
    close(sockfd);
}
