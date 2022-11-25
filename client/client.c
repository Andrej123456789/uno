/**
 * @author Andrej123456789 (Andrej Bartulin), nikhilroxtomar (Nikhil Tomar)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: client.c, C file for client
 * CREDITS: https://github.com/nikhilroxtomar/Chatroom-in-C
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

const char* logo_row1 = ".----------------.  .-----------------. .----------------.  .----------------.  .----------------.  \n";
const char* logo_row2 = "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n";
const char* logo_row3 = "| | _____  _____ | || | ____  _____  | || |     ____     | || |      _       | || |      _       | |\n";
const char* logo_row4 = "| ||_   _||_   _|| || ||_   \\|_   _| | || |   .'    `.   | || |     | |      | || |     | |      | |\n";
const char* logo_row5 = "| |  | |    | |  | || |  |   \\ | |   | || |  /  .--.  \\  | || |  ___| |___   | || |  ___| |___   | |\n";
const char* logo_row6 = "| |  | '    ' |  | || |  | |\\ \\| |   | || |  | |    | |  | || | |___   ___|  | || | |___   ___|  | |\n";
const char* logo_row7 = "| |   \\ `--' /   | || | _| |_\\   |_  | || |  \\  `--'  /  | || |     | |      | || |     | |      | |\n";
const char* logo_row8 = "| |    `.__.'    | || ||_____|\\____| | || |   `.____.'   | || |     |_|      | || |     |_|      | |\n";
const char* logo_row9 = "| |              | || |              | || |              | || |              | || |              | |\n";
const char* logo_row10 = "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------'|\n";
const char* logo_row11 = " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n";

#define LENGTH 2048

/* Global variables */
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[32];

/* Writes input text for player */
void str_overwrite_stdout()
{
    printf("%s", "Enter card id or do something else ['new' - take card from deck, 'all' - show all player's cards]:  ");
    fflush(stdout);
}

/* Removes new line char if it is placed on end of the string */
void str_trim_lf(char *arr, int length)
{
    int i;
    for (i = 0; i < length; i++)
    { /* trim \n */
        if (arr[i] == '\n')
        {
            arr[i] = '\0';
            break;
        }
    }
}

/* Catches Ctrl-C and exits; actually setting global variable named flag to 1 */
void catch_ctrl_c_and_exit(int sig)
{
    flag = 1;
}

/* Sends message to server */
void send_msg_handler()
{
    char message[LENGTH] = {};
    char buffer[LENGTH + 32] = {};

    while (1)
    {
        str_overwrite_stdout();
        fgets(message, LENGTH, stdin);
        str_trim_lf(message, LENGTH);

        if (strcmp(message, "exit") == 0)
        {
            break;
        }

        else
        {
            sprintf(buffer, "%s: %s\n", name, message);
            send(sockfd, buffer, strlen(buffer), 0);
        }

        bzero(message, LENGTH);
        bzero(buffer, LENGTH + 32);
    }
    catch_ctrl_c_and_exit(2);
}

/* Receives message from server or other player/players */
void recv_msg_handler()
{
    char message[LENGTH] = {};
    while (1)
    {
        int receive = recv(sockfd, message, LENGTH, 0);
        if (receive > 0)
        {
            printf("\n"); /* WARNING: be aware of this; this is here to save up some code in server */
            printf("%s", message);
            str_overwrite_stdout();
        }
        else if (receive == 0)
        {
            break;
        }
        else
        {
            // -1
        }
        memset(message, 0, sizeof(message));
    }
}

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <port>\n", argv[0]);
        return EXIT_SUCCESS;
    }

    char *ip = "127.0.0.1";
    int port = atoi(argv[1]);

    signal(SIGINT, catch_ctrl_c_and_exit);

    printf("Please enter your name: ");
    fgets(name, 32, stdin);
    str_trim_lf(name, strlen(name));

    if (strlen(name) > 32 || strlen(name) < 2)
    {
        printf("Name must be less than 30 and more than 2 characters.\n");
        return EXIT_FAILURE;
    }

    struct sockaddr_in server_addr;

    /* Socket settings */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_port = htons(port);

    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if (err == -1)
    {
        printf("ERROR: connect\n");
        return EXIT_FAILURE;
    }

    // Send name
    send(sockfd, name, 32, 0);

    char *logo = malloc(sizeof(char) * strlen(logo_row1) + strlen(logo_row2) + strlen(logo_row3) +
                        strlen(logo_row4) + strlen(logo_row5) + strlen(logo_row6) +
                        strlen(logo_row7) + strlen(logo_row8) + strlen(logo_row9) +
                        strlen(logo_row10) + strlen(logo_row11));

    strcat(logo, logo_row1);
    strcat(logo, logo_row2);
    strcat(logo, logo_row3);
    strcat(logo, logo_row4);
    strcat(logo, logo_row5);
    strcat(logo, logo_row6);
    strcat(logo, logo_row7);
    strcat(logo, logo_row8);
    strcat(logo, logo_row9);
    strcat(logo, logo_row10);
    strcat(logo, logo_row11);

    printf("%s\n", logo);
    free(logo);

    pthread_t send_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, (void *)send_msg_handler, NULL) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    pthread_t recv_msg_thread;
    if (pthread_create(&recv_msg_thread, NULL, (void *)recv_msg_handler, NULL) != 0)
    {
        printf("ERROR: pthread\n");
        return EXIT_FAILURE;
    }

    while (1)
    {
        if (flag)
        {
            printf("\nBye\n");
            break;
        }
    }

    close(sockfd);

    return EXIT_SUCCESS;
}
