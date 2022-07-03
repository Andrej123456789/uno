#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/* 
 * Naming convention for cards:
 *
 * Numbers:
 * 1 - 9 - number cards
 * 10 - +2 card
 * 11 - reverse card
 * 12 - skip card
 * 13 - wild card
 * 14 - wild draw four card
 * 
 * Colors:
 * 1 - red
 * 2- yellow
 * 3 - green
 * 4 - blue
*/

struct setting_t
{
    int players;
    int special_mode;
    int debug_mode;
    int swap_card;
};

struct cards_t
{
    int number;
    int color;
};

struct player_t
{
    struct cards_t cards[52];
    int number_of_cards;
};

struct runtime_t
{
    int avabible_cards;
    struct cards_t top_card[1];
};

static struct setting_t settings;

int ifFinished(int players);

void Gameplay(int players);
void SetCards(int players);
void Play(int players);