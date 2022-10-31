/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: client.c, client for C version
 * CREDITS: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <sys/socket.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

void func(int sockfd)
{
    char buff[MAX];
    int n;
    for (;;) 
    {
        bzero(buff, sizeof(buff));
        printf("Enter a message: ");

        n = 0;
        while ((buff[n++] = getchar()) != '\n')
            ;

        write(sockfd, buff, sizeof(buff));
        bzero(buff, sizeof(buff));
        read(sockfd, buff, sizeof(buff));

        buff[strlen(buff) - 1] = '\0';

        if (strcmp(buff, "") != 0)
        {
            printf("From server: '%s'\n", buff);
        }

        if ((strncmp(buff, "exit", 4)) == 0) 
        {
            printf("Received 'exit' from server! Exiting...\n");
            break;
        }
    }
}

int main()
{
    int sockfd, connfd;
    struct sockaddr_in servaddr, cli;
   
    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) 
    {
        printf("Socket creation failed! Exiting...\n");
        exit(0);
    }

    else
    {
        printf("Socket successfully created...\n");
    }

    bzero(&servaddr, sizeof(servaddr));
   
    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    servaddr.sin_port = htons(PORT);
   
    // connect the client socket to server socket
    if (connect(sockfd, (SA*)&servaddr, sizeof(servaddr)) != 0) 
    {
        printf("Connection with the server failed! Exiting...\n");
        exit(0);
    }

    else
    {
        printf("Connected to the server...\n");
    }
   
    func(sockfd);
    close(sockfd);
}
