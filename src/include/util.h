#pragma once

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include <stdio.h>
#include <stdlib.h>

#include "gameplay.h"

void bail(lua_State *L, char *msg);
void call(lua_State *L, char *file, char *function);
void copy(struct setting_t* settings, int players, int special_mode, int debug_mode, int swap_card, int colors);