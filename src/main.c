/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: main.c, entry point for the game
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pthread.h>

#include "include/runtime.h"
#include "include/util.h"
#include "include/gameplay.h"
#include "include/graphics.h"
#include "include/server.h"

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

void RunServer(void* arg)
{
    pthread_t tid[1];

    int err = 1;
    err = pthread_create(&(tid[0]), NULL, &StartServer, (void*)arg);
    if (err != 0)
    {
        printf("Can't create thread :[%s]\n", strerror(err));
    }

    else
    {
        printf("Thread created successfully\n");
    }
}

int main(int argc, const char** argv)
{
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

    /* Initial size is 20 including \0 character */
    char settings_path[256];

    if (argc == 2)
    {
        strncpy(settings_path, argv[1], 255);
    }

    else
    {
        printf("Usage: ./main <path to the settings file>\n");
        printf("Example: ./main settings/default.json\n");
        printf("\n");

        printf("Enter the path to the file: ");
        scanf("%255s", settings_path);
    }

    Runtime* runtime = malloc(sizeof(Runtime));

    runtime->current_card_id = 0;
    runtime->player_turn = 0;
    runtime->isPositive = true;

    Settings *settings = malloc(sizeof(Settings));
    Points *points = malloc(sizeof(Points));
    Theme *theme = malloc(sizeof(Theme));
    Network* network = malloc(sizeof(Network));

    copy_json(settings, points, network, settings_path);
    
    if (isNetworkPresent(settings))
    {
        Arg *arg = malloc(sizeof(Arg));

        arg->runtime = runtime;
        arg->network = network;
        RunServer(arg);
    }

    Gameplay(runtime, settings, points, theme);

    /* Frees structs */
    free(settings);
    free(points);
    free(theme);
    free(network);

    return 0;
}
