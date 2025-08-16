/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++
 * LICENSE: MIT license
 * DESCRIPTION: Client code (Windows)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>   // for _kbhit and _getch
#include <windows.h> // for Sleep

#pragma comment(lib, "ws2_32.lib")

#define BUFFER_LIMIT 255

char logo[11][106] =
{
    ".----------------.  .-----------------. .----------------.  .----------------.  .----------------.  ",
    "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |",
    "| | _____  _____ | || | ____  _____  | || |     ____     | || |      _       | || |      _       | |",
    "| ||_   _||_   _|| || ||_   \\|_   _| | || |   .'    `.   | || |     | |      | || |     | |      | |",
    "| |  | |    | |  | || |  |   \\ | |   | || |  /  .--.  \\  | || |  ___| |___   | || |  ___| |___   | |",
    "| |  | '    ' |  | || |  | |\\ \\| |   | || |  | |    | |  | || | |___   ___|  | || | |___   ___|  | |",
    "| |   \\ `--' /   | || | _| |_\\   |_  | || |  \\  `--'  /  | || |     | |      | || |     | |      | |",
    "| |    `.__.'    | || ||_____|\\____| | || |   `.____.'   | || |     |_|      | || |     |_|      | |",
    "| |              | || |              | || |              | || |              | || |              | |",
    "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |",
    " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'"
};

/**
 * Set non-blocking mode for socket
 * @param s SOCKET
 */
static int set_nonblocking(SOCKET s)
{
    u_long mode = 1;
    return ioctlsocket(s, FIONBIO, &mode);
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 11; i++)
    {
        printf("%s\n", logo[i]);
    }

    if (argc != 3)
    {
        fprintf(stderr, "use: %s <host> <port>\n", argv[0]);
        return 1;
    }

    /* --- Winsock init --- */
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
    {
        fprintf(stderr, "WSAStartup failed\n");
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == INVALID_SOCKET) {
        perror("socket");
        WSACleanup();
        return 1;
    }

    struct sockaddr_in srv;
    srv.sin_family = AF_INET;
    srv.sin_port = htons(atoi(argv[2]));
    if (inet_pton(AF_INET, argv[1], &srv.sin_addr) != 1 ||
        connect(sock, (struct sockaddr *)&srv, sizeof srv) != 0)
    {
        perror("connect");
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    set_nonblocking(sock);

    printf("Connected to %s:%s   (Ctrl-C to quit)\n", argv[1], argv[2]);

    char sbuf[BUFFER_LIMIT] = {0};   /* socket - stdout */
    char kbuf[BUFFER_LIMIT] = {0};   /* keyboard - socket */
    size_t klen = 0;

    /* --- main loop --- */
    while (1)
    {
        fd_set r;
        FD_ZERO(&r);
        FD_SET(sock, &r);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100000; // 100ms timeout so we can check keyboard

        int sel = select(0, &r, NULL, NULL, &tv);
        if (sel == SOCKET_ERROR)
        {
            perror("select");
            break;
        }

        /* --- data from server */
        if (FD_ISSET(sock, &r))
        {
            int n = recv(sock, sbuf, sizeof sbuf - 1, 0);
            if (n <= 0)
            {
                puts("\n[disconnected]");
                break;
            }

            sbuf[n] = '\0';
            printf("%s", sbuf);
            fflush(stdout);
        }

        /* --- data from keyboard */
        while (_kbhit())
        {
            char ch = _getch();
            if (ch == '\r') // Enter
            {
                kbuf[klen++] = '\n';
                send(sock, kbuf, (int)klen, 0);
                klen = 0;
                memset(kbuf, 0, sizeof kbuf);
                printf("\n"); // echo newline locally
            }

            else if (ch == '\b') // Backspace
            {
                if (klen > 0) 
                {
                    klen--;
                    printf("\b \b"); // erase locally
                }
            }

            else if (klen < BUFFER_LIMIT - 2) 
            {
                kbuf[klen++] = ch;
                putchar(ch); // echo locally
            }

            fflush(stdout);
        }

        Sleep(10); // avoid busy loop
    }

    closesocket(sock);
    WSACleanup();

    return 0;
}
