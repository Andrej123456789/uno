/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: gameplay.h, header file for gameplay mechanics
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#include "runtime.h"
#include "graphics.h"
#include "strings.h"
#include "c_vector.h"
#include "server.h"

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
 * Checks is there any network player
 * @param settings - struct which contains information about settings, points to setting_T
*/
bool isNetworkPresent(Settings* settings);

/**
 * Check if some player finished the round.
 * @param players - number of players
 * @param player - struct which contains information about player, points to player_T
 * @param points - struct for holding information about points, points to points_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
bool isFinished(Player player[], Points* points, Settings* settings);

/**
 * Check if cards which player wants to play is compatible with the top card.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
*/
bool isCompatible(Runtime* runtime, Player players_card[]);

/**
 * Generates a deck of cards
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @return vector which contains cards
*/
cvector_vector_type(Cards) GenerateDeck(Runtime* runtime, Settings* settings);

/**
 * Swap cards bettwen two players.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param swap_id - player which will got the cards from player which asked for swap
*/
void Swap(Runtime* runtime, Player player[], Settings* settings, int swap_id);

/**
 * Switch turn to the next player.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param doReturn - do return of next player turn 
*/
int NextPlayer(Runtime* runtime, Settings* settings, bool doReturn);

/**
 * Perform action on the card which user wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param stacking - struct which contains information about stacking, points to stacking_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void Action(Runtime* runtime, Player player[], Stacking* stacking, Cards cards[], Settings* settings);

/**
 * Perform action on the top card.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param stacking - struct which contains information about stacking, points to stacking_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void TopCardAction(Runtime* runtime, Player player[], Stacking* stacking, Cards cards[], Settings* settings);

/**
 * Perform an action on the card which AI wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param stacking - struct which contains information about stacking, points to stacking_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void AIAction(Runtime* runtime, Player player[], Stacking* stacking, Cards cards[], Settings* settings);

/**
 * Read or write points to text file.
 * @param points - struct for holding information about points, points to points_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param write - perform read of write
 * @param players - number of players
 * @param point - points, see function code in gameplay.c for naming convention
*/
int PointsFromFile(Points* points, Settings* settings, bool write, int player, int point);

/**
 * Assigning points and determining winner of the match.
 * @param player - struct which contains information about player, points to player_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param points - struct for holding information about points, points to points_T
 * @param players - number of players
*/
void PointsManager(Player player[], Settings* settings, Points* points, int players);

/**
 * Entry point for gameplay mechanics, calls all other functions in gameplay.h and gameplay.c.
 * @param settings - struct which contains information about settings, points to setting_T
 * @param points - struct for holding information about points, points to points_T
 * @param theme - struct for holding graphics (theme releated stuff mostly) informations during runtime, points to theme_T
 * @param network - struct which holds all informations on network, points to network_T
*/
void Gameplay(Settings* settings, Points* points, Theme* theme);
