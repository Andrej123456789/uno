#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

#include <stdio.h>

int main(int argc, char *argv[]) 
{
    printf(" \n ");
    printf("\tNETWORK UNO - Uno in terminal with network in mind\n");
    printf(" \n ");

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "main.lua");

    lua_close(L);
    return 0;
}