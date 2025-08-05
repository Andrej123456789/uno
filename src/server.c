/**
 * @author nikhilroxtomar (Nikhil Tomar)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache-2.0 license
 * DESCRIPTION: server.c, C file for a server
 * CREDITS: https://github.com/nikhilroxtomar/Chatroom-in-C
*/

/*
                                 Apache License
                           Version 2.0, January 2004
                        http://www.apache.org/licenses/

   TERMS AND CONDITIONS FOR USE, REPRODUCTION, AND DISTRIBUTION

   1. Definitions.

      "License" shall mean the terms and conditions for use, reproduction,
      and distribution as defined by Sections 1 through 9 of this document.

      "Licensor" shall mean the copyright owner or entity authorized by
      the copyright owner that is granting the License.

      "Legal Entity" shall mean the union of the acting entity and all
      other entities that control, are controlled by, or are under common
      control with that entity. For the purposes of this definition,
      "control" means (i) the power, direct or indirect, to cause the
      direction or management of such entity, whether by contract or
      otherwise, or (ii) ownership of fifty percent (50%) or more of the
      outstanding shares, or (iii) beneficial ownership of such entity.

      "You" (or "Your") shall mean an individual or Legal Entity
      exercising permissions granted by this License.

      "Source" form shall mean the preferred form for making modifications,
      including but not limited to software source code, documentation
      source, and configuration files.

      "Object" form shall mean any form resulting from mechanical
      transformation or translation of a Source form, including but
      not limited to compiled object code, generated documentation,
      and conversions to other media types.

      "Work" shall mean the work of authorship, whether in Source or
      Object form, made available under the License, as indicated by a
      copyright notice that is included in or attached to the work
      (an example is provided in the Appendix below).

      "Derivative Works" shall mean any work, whether in Source or Object
      form, that is based on (or derived from) the Work and for which the
      editorial revisions, annotations, elaborations, or other modifications
      represent, as a whole, an original work of authorship. For the purposes
      of this License, Derivative Works shall not include works that remain
      separable from, or merely link (or bind by name) to the interfaces of,
      the Work and Derivative Works thereof.

      "Contribution" shall mean any work of authorship, including
      the original version of the Work and any modifications or additions
      to that Work or Derivative Works thereof, that is intentionally
      submitted to Licensor for inclusion in the Work by the copyright owner
      or by an individual or Legal Entity authorized to submit on behalf of
      the copyright owner. For the purposes of this definition, "submitted"
      means any form of electronic, verbal, or written communication sent
      to the Licensor or its representatives, including but not limited to
      communication on electronic mailing lists, source code control systems,
      and issue tracking systems that are managed by, or on behalf of, the
      Licensor for the purpose of discussing and improving the Work, but
      excluding communication that is conspicuously marked or otherwise
      designated in writing by the copyright owner as "Not a Contribution."

      "Contributor" shall mean Licensor and any individual or Legal Entity
      on behalf of whom a Contribution has been received by Licensor and
      subsequently incorporated within the Work.

   2. Grant of Copyright License. Subject to the terms and conditions of
      this License, each Contributor hereby grants to You a perpetual,
      worldwide, non-exclusive, no-charge, royalty-free, irrevocable
      copyright license to reproduce, prepare Derivative Works of,
      publicly display, publicly perform, sublicense, and distribute the
      Work and such Derivative Works in Source or Object form.

   3. Grant of Patent License. Subject to the terms and conditions of
      this License, each Contributor hereby grants to You a perpetual,
      worldwide, non-exclusive, no-charge, royalty-free, irrevocable
      (except as stated in this section) patent license to make, have made,
      use, offer to sell, sell, import, and otherwise transfer the Work,
      where such license applies only to those patent claims licensable
      by such Contributor that are necessarily infringed by their
      Contribution(s) alone or by combination of their Contribution(s)
      with the Work to which such Contribution(s) was submitted. If You
      institute patent litigation against any entity (including a
      cross-claim or counterclaim in a lawsuit) alleging that the Work
      or a Contribution incorporated within the Work constitutes direct
      or contributory patent infringement, then any patent licenses
      granted to You under this License for that Work shall terminate
      as of the date such litigation is filed.

   4. Redistribution. You may reproduce and distribute copies of the
      Work or Derivative Works thereof in any medium, with or without
      modifications, and in Source or Object form, provided that You
      meet the following conditions:

      (a) You must give any other recipients of the Work or
          Derivative Works a copy of this License; and

      (b) You must cause any modified files to carry prominent notices
          stating that You changed the files; and

      (c) You must retain, in the Source form of any Derivative Works
          that You distribute, all copyright, patent, trademark, and
          attribution notices from the Source form of the Work,
          excluding those notices that do not pertain to any part of
          the Derivative Works; and

      (d) If the Work includes a "NOTICE" text file as part of its
          distribution, then any Derivative Works that You distribute must
          include a readable copy of the attribution notices contained
          within such NOTICE file, excluding those notices that do not
          pertain to any part of the Derivative Works, in at least one
          of the following places: within a NOTICE text file distributed
          as part of the Derivative Works; within the Source form or
          documentation, if provided along with the Derivative Works; or,
          within a display generated by the Derivative Works, if and
          wherever such third-party notices normally appear. The contents
          of the NOTICE file are for informational purposes only and
          do not modify the License. You may add Your own attribution
          notices within Derivative Works that You distribute, alongside
          or as an addendum to the NOTICE text from the Work, provided
          that such additional attribution notices cannot be construed
          as modifying the License.

      You may add Your own copyright statement to Your modifications and
      may provide additional or different license terms and conditions
      for use, reproduction, or distribution of Your modifications, or
      for any such Derivative Works as a whole, provided Your use,
      reproduction, and distribution of the Work otherwise complies with
      the conditions stated in this License.

   5. Submission of Contributions. Unless You explicitly state otherwise,
      any Contribution intentionally submitted for inclusion in the Work
      by You to the Licensor shall be under the terms and conditions of
      this License, without any additional terms or conditions.
      Notwithstanding the above, nothing herein shall supersede or modify
      the terms of any separate license agreement you may have executed
      with Licensor regarding such Contributions.

   6. Trademarks. This License does not grant permission to use the trade
      names, trademarks, service marks, or product names of the Licensor,
      except as required for reasonable and customary use in describing the
      origin of the Work and reproducing the content of the NOTICE file.

   7. Disclaimer of Warranty. Unless required by applicable law or
      agreed to in writing, Licensor provides the Work (and each
      Contributor provides its Contributions) on an "AS IS" BASIS,
      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or
      implied, including, without limitation, any warranties or conditions
      of TITLE, NON-INFRINGEMENT, MERCHANTABILITY, or FITNESS FOR A
      PARTICULAR PURPOSE. You are solely responsible for determining the
      appropriateness of using or redistributing the Work and assume any
      risks associated with Your exercise of permissions under this License.

   8. Limitation of Liability. In no event and under no legal theory,
      whether in tort (including negligence), contract, or otherwise,
      unless required by applicable law (such as deliberate and grossly
      negligent acts) or agreed to in writing, shall any Contributor be
      liable to You for damages, including any direct, indirect, special,
      incidental, or consequential damages of any character arising as a
      result of this License or out of the use or inability to use the
      Work (including but not limited to damages for loss of goodwill,
      work stoppage, computer failure or malfunction, or any and all
      other commercial damages or losses), even if such Contributor
      has been advised of the possibility of such damages.

   9. Accepting Warranty or Additional Liability. While redistributing
      the Work or Derivative Works thereof, You may choose to offer,
      and charge a fee for, acceptance of support, warranty, indemnity,
      or other liability obligations and/or rights consistent with this
      License. However, in accepting such obligations, You may act only
      on Your own behalf and on Your sole responsibility, not on behalf
      of any other Contributor, and only if You agree to indemnify,
      defend, and hold each Contributor harmless for any liability
      incurred by, or claims asserted against, such Contributor by reason
      of your accepting any such warranty or additional liability.

   END OF TERMS AND CONDITIONS

   APPENDIX: How to apply the Apache License to your work.

      To apply the Apache License to your work, attach the following
      boilerplate notice, with the fields enclosed by brackets "[]"
      replaced with your own identifying information. (Don't include
      the brackets!)  The text should be enclosed in the appropriate
      comment syntax for the file format. We also recommend that a
      file or class name and description of purpose be included on the
      same "printed page" as the copyright notice for easier
      identification within third-party archives.

   Copyright [yyyy] [name of copyright owner]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include "include/server.h"

#include <math.h>
#include <stdarg.h>

static _Atomic unsigned int cli_count = 0;
static int uid = 10;

static cvector_vector_type(client_t *) clients;
static pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

typedef struct
{
    client_t* cli;
    Runtime* runtime;
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

                const char* sub = malloc(sizeof(char) + strlen(cli->name) + 3);
                strcat(sub, cli->name);
                strcat(sub, ": ");

                const char* buffer = malloc(strlen(strremove(buff_out, sub)));
                strcpy(buffer, strremove(buff_out, sub));

                printf("%s\n", buffer);
                free(sub);

                int digits = (actual_arg_2->runtime->player_turn == 0) ? 1 : (log10(actual_arg_2->runtime->player_turn) + 1);
                printf("Digits: %d\n", digits);

                if (strrchr(cli->name, '\0') - digits == actual_arg_2->runtime->player_turn)
                {
                    printf("Your turn!\n");
                }

                else
                {
                    printf("Not your turn!\n%d | %d\n", actual_arg_2->runtime->player_turn, strrchr(cli->name, '\0') - digits);
                }

                free(buffer);
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
        return NULL;
    }

    /* Bind */
    if (bind(listenfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        perror("ERROR: Socket binding failed");
        return NULL;
    }

    /* Listen */
    if (listen(listenfd, 10) < 0)
    {
        perror("ERROR: Socket listening failed");
        return NULL;
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
        arg2->network = actual_arg->network;

        arg2->runtime = actual_arg->runtime;

        /* Add client to the queue and fork thread */
        queue_add(cli);
        pthread_create(&tid, NULL, &handle_client, (void *)arg2);

        /* Reduce CPU usage */
        sleep(1);
    }

    return NULL;
}
