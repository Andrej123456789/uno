#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "include/util.h"
#include "include/setup.h"
#include "include/gameplay.h"

const char* logo_row1= " .----------------.  .-----------------. .----------------.  .----------------.  .----------------.  \n";
const char* logo_row2 = "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |\n";
const char* logo_row3 = "| | _____  _____ | || | ____  _____  | || |     ____     | || |      _       | || |      _       | |\n";
const char* logo_row4 = "| ||_   _||_   _|| || ||_   \|_   _| | || |   .'    `.   | || |     | |      | || |     | |      | |\n";
const char* logo_row5 = "| |  | |    | |  | || |  |   \ | |   | || |  /  .--.  \  | || |  ___| |___   | || |  ___| |___   | |\n";
const char* logo_row6 = "| |  | '    ' |  | || |  | |\ \| |   | || |  | |    | |  | || | |___   ___|  | || | |___   ___|  | |\n";
const char* logo_row7 = "| |   \ `--' /   | || | _| |_\   |_  | || |  \  `--'  /  | || |     | |      | || |     | |      | |\n";
const char* logo_row8 = "| |    `.__.'    | || ||_____|\____| | || |   `.____.'   | || |     |_|      | || |     |_|      | |\n";
const char* logo_row9 = "| |              | || |              | || |              | || |              | || |              | |\n";
const char* logo_row10 = "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------'|\n";
const char* logo_row11 = " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'\n";

char logo[];
int players;

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

    /* lua_State *L;
    call(L, "main.lua", "Hello"); */

    if (argc > 1)
    {
        players = atoi(argv[1]);
    }

    else
    {
        printf("Usage: ./main <players>\n");
        printf("Example: ./main 2\n");
        printf("\n");

        printf("Enter number of players: ");
        scanf("%d", &players);
    }

    Setup();
    Gameplay(players);

    return 0;
}