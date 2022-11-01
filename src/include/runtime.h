/**
 * @author: Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: runtime.h, header file for all runtime informations
*/

#pragma once

#include <stdbool.h>
#include "vec.h"
#include "c_vector.h"

/* Max number of players */
#define MAX_PLAYERS 20

/**
 * Struct which contains the settings of the game.
 * @param debug_mode - debug mode (0 - off, 1 - on)
 * @param colors - colors (0 - off, 1 - on)
 * @param players - number of players
 * @param special - contains settings for "special elements", swap card, stacking, seven_o, jump_in
 * @param ai_sequence - vector which contains which players are AI
 * @param network_sequence - vector which contains which players are connected on the network
*/
typedef struct settings_T
{
    int debug_mode;
    int colors;
    int players;
    int special[4];
    cvector_vector_type(char) ai_sequence;
    cvector_vector_type(char) network_sequence;
} Settings;

/**
 * Struct which contains the cards information.
 * @param number - the number of the card
 * @param color - the color of the card
*/
typedef struct cards_T
{
    int number;
    int color;
} Cards;

/**
 * Struct which contains informations about player.
 * @param cards - vector which contains cards
 * @param points - points which player has
 * @param legal_four - can player legally play wild draw four card
*/
typedef struct player_T
{
    cvector_vector_type(Cards) cards;
    int points;
    bool legal_four;
} Player;

/**
 * Struct for holding information during the game.
 * @param available_cards - cards that are available for the players
 * @param current_card_id - current card id
 * @param player_turn - player turn
 * @param isPositive - determines if the turn is positive or negative.
 * @param top_card - array which holds information about the top card
 * @param top_card.number - number of the top card
 * @param top_card.color - color of the top card
*/
typedef struct runtime_T
{
    int avabible_cards;
    int current_card_id;
    int player_turn;
    bool isPositive;
    Cards top_card[1];
} Runtime;

/** Struct for holding stacking information
 * @param happening - is stacking happening right now
 * @param number - is card +2 or +4
 * @param number_of_cards - how much we already stacked
*/
typedef struct stacking_T
{
    bool happening;
    int number;
    int number_of_cards;
} Stacking ;

/**
 * Everything releated to points in game is here, even if it is should be in another struct.
 * @param points_path - path of file where are points stored
 * @param temp_points - points in the round
 * @param match_points - points needed to win the match
 * @param round_winner - player id who won the round
 * @param match_winner - player id who won the match
 * @param match_ended - if the match has ended
 * @param alReadyCreated - if file for points is already created
*/
typedef struct points_T
{
    char points_path[1024];
    int temp_points;
    int match_points;
    int round_winner;
    int match_winner;
    bool match_ended;
    bool alReadyCreated;
} Points;

/** Struct which holds graphics (theme releated stuff mostly) informations during runtime
 * @param dark - light or dark theme
*/
typedef struct theme_T
{
    bool dark;
} Theme;
