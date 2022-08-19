/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: server.c, header file for a server for C version
 * CREDITS: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>

#define MAX 80
#define PORT 8080
#define SA struct sockaddr

/**
 * Sending/receiving text to/from client
 * @param connfd - something important but currently idk what is that
*/
void SendReceive(int connfd);

/**
 * Start a server
*/
void StartServer();
