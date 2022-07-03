#include "include/util.h"
#include "include/gameplay.h"

void bail(lua_State *L, char *msg)
{
	fprintf(stderr, "\nFATAL ERROR:\n  %s: %s\n\n",
		msg, lua_tostring(L, -1));
	exit(1);
}

void call(lua_State *L, char *file, char *function)
{
    L = luaL_newstate();                        /* Create Lua state variable */
    luaL_openlibs(L);                           /* Load Lua libraries */

    if (luaL_loadfile(L, file))                 /* Load but don't run the Lua script */
	    bail(L, "luaL_loadfile() failed");      /* Error out if file can't be read */

    if (lua_pcall(L, 0, 0, 0))                  /* PRIMING RUN. FORGET THIS AND YOU'RE TOAST */
	    bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */

    lua_getglobal(L, function);                 /* Tell what function to run */

    if (lua_pcall(L, 0, 0, 0))                  /* Run the function */
	    bail(L, "lua_pcall() failed");          /* Error out if Lua file has an error */

    lua_close(L);                               /* Clean up, free the Lua state var */
}

void copy(int players, int special_mode, int debug_mode, int swap_card)
{
    settings.players = players;
    settings.special_mode = special_mode;
    settings.debug_mode = debug_mode;
    settings.swap_card;
}