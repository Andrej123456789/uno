#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
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
 * 2 - yellow
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
    int current_card_id;
    int player_turn;
    struct cards_t top_card[1];
};

static bool isPositive = true;

bool isFinished(int players, struct player_t player[]);
bool isCompatible(struct runtime_t* runtime, struct player_t player[]);
void NextPlayer(struct runtime_t* runtime, int players, bool isPositive);
void Action(struct runtime_t* runtime, struct player_t player[], struct cards_t cards[], int players);
void TopCardAction(struct runtime_t* runtime, struct player_t player[], struct cards_t cards[], int players);
void Gameplay(struct setting_t* settings, int players);