/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: gameplay.h, header file for gameplay mechanics
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/* Max number of players */
#define MAX_PLAYERS 20

/*
 * Naming convention for cards:
 *
 * Numbers:
 * 0 - 9 - number cards
 * 10 - +2 card
 * 11 - reverse card
 * 12 - skip card
 * 13 - wild card
 * 14 - wild draw four card
 * 15 - swap card
 * 
 * Colors:
 * 1 - red
 * 2 - yellow
 * 3 - green
 * 4 - blue
*/

/**
 * Struct which contains the settings of the game.
 * @param players - number of players
 * @param special_mode - special mode (0 - off, 1 - on)
 * @param debug_mode - debug mode (0 - off, 1 - on)
 * @param swap_card - swap card (0 - off, 1 - on)
 * @param colors - colors (0 - off, 1 - on)
 * @param ai_sequence - contains which players are AI (needs to be written reversed)
 * @param ai_array_sequence - ai_sequence in array form
 * @param network_sequence - contains which players are network players (needs to be written reversed)
 * @param network_array_sequence - network_sequence in array form
*/
struct setting_t
{
    int players;
    int special_mode;
    int debug_mode;
    int swap_card;
    int colors;
	char json_ai_sequence[MAX_PLAYERS];
	char json_network_sequence[MAX_PLAYERS];
};

/**
 * Struct which contains the cards information.
 * @param number - the number of the card
 * @param color - the color of the card
*/
struct cards_t
{
    int number;
    int color;
};

/**
 * Struct which contains informations about player.
 * @param cards - array of cards which player has
 * @param cards.number - number of card
 * @param cards.color - color of card
 * @param number_of_cards - number of cards which player has
 * @param points - points which player has
*/
struct player_t
{
    struct cards_t cards[52];
    int number_of_cards;
    int points;
};

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
struct runtime_t
{
    int avabible_cards;
    int current_card_id;
    int player_turn;
    bool isPositive;
    struct cards_t top_card[1];
};

/**
 * Everything releated to points in game is here, even if it is should be in another struct.
 * @param temp_points - points in the round
 * @param match_points - points needed to win the match
 * @param round_winner - player id who won the round
 * @param match_winner - player id who won the match
 * @param match_ended - if the match has ended
 * @param alReadyCreated - if file for points is already created
*/
struct points_t
{
    int temp_points;
    int match_points;
    int round_winner;
    int match_winner;
    bool match_ended;
    bool alReadyCreated;
};

/**
 * Check if some player finished the round.
 * @param players - number of players
 * @param player - struct which contains information about player, pointing to player_t
 * @param points - struct for holding information about points, pointing to points_t
*/
bool isFinished(int players, struct player_t player[], struct points_t* points);

/**
 * Check if cards which player wants to play is compatible with the top card.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param player - struct which contains information about player, pointing to player_t
*/
bool isCompatible(struct runtime_t* runtime, struct player_t player[]);

/**
 * Swap cards bettwen two players.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param player - struct which contains information about player, pointing to player_t
 * @param swap_id - player which will got the cards from player which asked for swap
*/
void Swap(struct runtime_t* runtime, struct player_t player[], int swap_id);

/**
 * Switch turn to the next player.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param players - number of players
 * @param doReturn - do return of next player turn 
*/
int NextPlayer(struct runtime_t* runtime, int players, bool doReturn);

/**
 * Perform action on the card which user wants to play.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param player - struct which contains information about player, pointing to player_t
 * @param cards - struct which contains information about cards, pointing to cards_t
 * @param settings - struct which contains information about settings, pointing to setting_t
 * @param players - number of players
*/
void Action(struct runtime_t* runtime, struct player_t player[], struct cards_t cards[], struct setting_t* settings, int players);

/**
 * Perform action on the top card.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param player - struct which contains information about player, pointing to player_t
 * @param cards - struct which contains information about cards, pointing to cards_t
 * @param players - number of players
*/
void TopCardAction(struct runtime_t* runtime, struct player_t player[], struct cards_t cards[], int players);

/**
 * Determine which player is AI.
 * @param settings - struct which contains information about settings, pointing to setting_t 
*/
int SetAISequence(struct setting_t* settings);

/**
 * Perform an action on the card which AI wants to play.
 * @param runtime - struct for holding information during the game, pointing to runtime_t
 * @param player - struct which contains information about player, pointing to player_t
 * @param cards - struct which contains information about cards, pointing to cards_t
 * @param settings - struct which contains information about settings, pointing to setting_t
 * @param players - number of players 
*/
void AIAction(struct runtime_t* runtime, struct player_t player[], struct cards_t cards[], struct setting_t* settings, int players);

/**
 * Determine which player is connected to network.
 * @param settings - struct which contains information about settings, pointing to setting_t 
*/
int SetNetworkSequence(struct setting_t* settings);

/**
 * Read or write points to text file.
 * @param points - struct for holding information about points, pointing to points_t
 * @param settings - struct which contains information about settings, pointing to setting_t
 * @param write - perform read of write
 * @param players - number of players
 * @param point - points, see function code in gameplay.c for naming convention
*/
int PointsFromFile(struct points_t* points, struct setting_t* settings, bool write, int player, int point);

/**
 * Assigning points and determining winner of the match.
 * @param player - struct which contains information about player, pointing to player_t
 * @param settings - struct which contains information about settings, pointing to setting_t
 * @param points - struct for holding information about points, pointing to points_t
 * @param players - number of players
*/
void PointsManager(struct player_t player[], struct setting_t* settings, struct points_t* points, int players);

/**
 * Entry point for gameplay mechanics, calls all other functions in gameplay.h and gameplay.c.
 * @param settings - struct which contains information about settings, pointing to setting_t
 * @param points - struct for holding information about points, pointing to points_t 
*/
void Gameplay(struct setting_t* settings, struct points_t* points);
