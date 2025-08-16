/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++
 * LICENSE: MIT license
 * DESCRIPTION: Server code (Windows)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>

#include "../include/gameplay.h"
#include "../include/server.h"

#pragma comment(lib, "ws2_32.lib")

/**
 * Enables non-blocking mode on a socket.
 * @param s SOCKET
 */
static int set_nonblocking(SOCKET s)
{
    u_long mode = 1;
    return ioctlsocket(s, FIONBIO, &mode);
}

int net_start_server(uint16_t port, uint16_t number_of_players)
{
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        fprintf(stderr, "WSAStartup failed\n");
        return -1;
    }

    SOCKET s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET) { fprintf(stderr, "socket error\n"); return -1; }

    int yes = 1;
    setsockopt(s, SOL_SOCKET, SO_REUSEADDR, (const char*)&yes, sizeof(yes));

    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(s, (struct sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR ||
        listen(s, number_of_players) == SOCKET_ERROR ||
        set_nonblocking(s) != 0)
    {
        fprintf(stderr, "net_start_server failed: %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return -1;
    }

    fprintf(stderr, "[server] listening on %u\n", port);
    return (int)s;
}

void net_accept_clients(SOCKET listener_fd, Player* players, int number_of_players)
{
    for (;;)
    {
        struct sockaddr_in cli;
        int len = sizeof(cli);
        SOCKET c = accept(listener_fd, (struct sockaddr*)&cli, &len);

        if (c == INVALID_SOCKET)
        {
            int err = WSAGetLastError();
            if (err != WSAEWOULDBLOCK) fprintf(stderr, "accept error: %d\n", err);
            break;
        }

        if (set_nonblocking(c) != 0) { fprintf(stderr, "ioctlsocket error\n"); closesocket(c); continue; }

        int i;
        for (i = 0; i < number_of_players; ++i)
        {
            if (players[i].network.sockfd <= 0) break;
        }

        if (i == number_of_players)
        {
            const char msg[] = "Server is full.\n";
            send(c, msg, sizeof(msg), 0); closesocket(c); continue;
        }

        players[i].network.sockfd = (int)c;
        players[i].network.ready = false;
        players[i].network.inbuf[0] = '\0';

        fprintf(stderr, "[server] client %d bound to player %d (%s)\n",
                (int)c, i, inet_ntoa(cli.sin_addr));
    }
}

void net_poll_clients(Player* players, int number_of_players)
{
    fd_set rfds;
    FD_ZERO(&rfds);
    SOCKET maxfd = 0;

    for (int i = 0; i < number_of_players; ++i)
    {
        SOCKET s = (SOCKET)players[i].network.sockfd;
        if (s != INVALID_SOCKET && s > 0) { FD_SET(s, &rfds); if (s > maxfd) maxfd = s; }
    }

    if (maxfd == 0) return;

    struct timeval tv = {0,0};
    if (select(0, &rfds, NULL, NULL, &tv) <= 0) return;

    char ch;
    for (int i = 0; i < number_of_players; ++i)
    {
        SOCKET s = (SOCKET)players[i].network.sockfd;
        if (s <= 0 || !FD_ISSET(s, &rfds)) continue;

        while (recv(s, &ch, 1, 0) == 1)
        {
            if (ch == '\r') continue;
            if (ch == '\n') { players[i].network.ready = true; break; }
            size_t l = strlen(players[i].network.inbuf);
            if (l < BUFFER_LIMIT) { players[i].network.inbuf[l]=ch; players[i].network.inbuf[l+1]='\0'; }
        }
    }
}

static void vsend(SOCKET s, const char* fmt, va_list ap)
{
    char buf[BUFFER_LIMIT];
    int n = vsnprintf(buf, sizeof(buf), fmt, ap);
    if (n < 0) return;
    send(s, buf, (size_t)n, 0);
}

void send_to_player(Player* p, const char* fmt, ...)
{
    if (p->network.sockfd <= 0) return;
    va_list ap; va_start(ap, fmt);
    vsend((SOCKET)p->network.sockfd, fmt, ap);
    va_end(ap);
}

void broadcast(Player* players, int number_of_players, const char* fmt, ...)
{
    va_list ap1, ap2;
    va_start(ap1, fmt);

    for (int i = 0; i < number_of_players; ++i)
    {
        SOCKET s = (SOCKET)players[i].network.sockfd;
        if (s <= 0) continue;

        va_copy(ap2, ap1);
        char buf[BUFFER_LIMIT];
        int n = vsnprintf(buf, sizeof(buf), fmt, ap2);
        va_end(ap2);
        if (n > 0) send(s, buf, (size_t)n, 0);
    }

    va_end(ap1);
}
