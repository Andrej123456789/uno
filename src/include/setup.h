#pragma once

#include <stdio.h>

typedef struct Settings
{
    int special_mode;
    int debug_mode;
    int swap_card;
} settings ;

static settings set; /* idk better name */

void Setup();