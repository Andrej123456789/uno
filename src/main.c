/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: main.c, entry point for the game
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/util.h"
#include "include/gameplay.h"

const char* logo_row1 = ".----------------.  .-----------------. .----------------.  .----------------.  .----------------.  \n";
const char* logo_row2 = "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n";
const char* logo_row3 = "| | _____  _____ | || | ____  _____  | || |     ____     | || |      _       | || |      _       | |\n";
const char* logo_row4 = "| ||_   _||_   _|| || ||_   \|_   _| | || |   .'    `.   | || |     | |      | || |     | |      | |\n";
const char* logo_row5 = "| |  | |    | |  | || |  |   \ | |   | || |  /  .--.  \  | || |  ___| |___   | || |  ___| |___   | |\n";
const char* logo_row6 = "| |  | '    ' |  | || |  | |\ \| |   | || |  | |    | |  | || | |___   ___|  | || | |___   ___|  | |\n";
const char* logo_row7 = "| |   \ `--' /   | || | _| |_\   |_  | || |  \  `--'  /  | || |     | |      | || |     | |      | |\n";
const char* logo_row8 = "| |    `.__.'    | || ||_____|\____| | || |   `.____.'   | || |     |_|      | || |     |_|      | |\n";
const char* logo_row9 = "| |              | || |              | || |              | || |              | || |              | |\n";
const char* logo_row10 ="| '--------------' || '--------------' || '--------------' || '--------------' || '--------------'|\n";
const char* logo_row11 =" '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n";

char logo[];
int players;

char path[20];
char temp[];

int main(int argc, const char **argv)
{
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
    printf("\t\t\t\t\t Sorry for bad look! \t \n\n");

    if (argc == 2)
    {
        if (strlen(argv[1]) < 20)
        {
            strcpy(path, argv[1]);
        }

        else
        {
            printf("Path is too long!\n");
            return 0;
        }
    }

    else
    {
        printf("Usage: ./main <path to file>\n");
        printf("Example: ./main default.txt\n");
        printf("\n");

        printf("Enter the path to the file: ");
        scanf("%s", temp);

        if (strlen(temp) < 20)
        {
            strcpy(path, temp);
        }

        else
        {
            printf("Path is too long!\n");
        }
    }

    struct setting_t* settings = malloc(sizeof(struct setting_t));
    struct points_t* points = malloc(sizeof(struct points_t));

    if (copy(settings, points, path) == 0)
    {
        Gameplay(settings, points);
    }

    free(settings);
    return 0;
}