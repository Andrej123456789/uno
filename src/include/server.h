/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: server.c, header file for a server for C version
 * CREDITS: https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <signal.h>

#include "util.h"
#include "strings.h"
#include "c_vector.h"

#define BUFFER_SZ 2048

/* Client structure */
typedef struct
{
    struct sockaddr_in address;
    int sockfd;
    int uid;
    char name[32];
} client_t;

/* Overwrites stdout */
void str_overwrite_stdout();

/** 
 * Removes last element from array if it is new line char 
 * @param arr - array
 * @param length - length
*/ 
void str_trim_lf(char *arr, int length);

/**
 * Removes substring in passed string
 * @param str - string
 * @param sub - substring to be removed
*/
char *strremove(char *str, const char *sub);

/** 
 * Prints address of client
 * @param addr - address of client
*/
void print_client_addr(struct sockaddr_in addr);

/** 
 * Adds clients to queue 
 * @param cl - client
*/
void queue_add(client_t *cl);

/** 
 * Removes clients to queue
 * @param uid - id (position in vector) of client
*/
void queue_remove(int uid);

/**
 * Send message to all clients except sender
 * @param s - string
 * @param uid - id (position in vector) of client
*/
void send_message(char *s, int uid);

/**
 * Sends message to all clients 
 * @param s - string
*/
void send_message_all(const char *s, ...);

/**
 * Sends message to specified client
 * @param id - client id, aka position in vector
 * @param s - string
*/
void send_message_to(int id, const char* s, ...);

/**
 * Handles all communication with the client
 * @param arg - argument(s)
*/
void *handle_client(void *arg);

/**
 * Starts a server 
 * @param arg - argument(s)
*/
void* StartServer(void* arg);
