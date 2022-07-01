#pragma once

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void bail(lua_State *L, char *msg);
void call(lua_State *L, char *file, char *function);