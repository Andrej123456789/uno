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

#include "runtime.h"
#include "graphics.h"
#include "strings.h"

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
 * Check if some player finished the round.
 * @param players - number of players
 * @param player - struct which contains information about player, points to player_t
 * @param points - struct for holding information about points, points to points_t
*/
bool isFinished(int players, Player player[], Points* points);

/**
 * Check if cards which player wants to play is compatible with the top card.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param player - struct which contains information about player, points to player_t
*/
bool isCompatible(Runtime* runtime, Player players_card[]);

/**
 * Swap cards bettwen two players.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param player - struct which contains information about player, points to player_t
 * @param swap_id - player which will got the cards from player which asked for swap
*/
void Swap(Runtime* runtime, Player player[], int swap_id);

/**
 * Switch turn to the next player.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param settings - struct which contains information about settings, points to setting_t
 * @param doReturn - do return of next player turn 
*/
int NextPlayer(Runtime* runtime, Settings* settings, bool doReturn);

/**
 * Perform action on the card which user wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param player - struct which contains information about player, points to player_t
 * @param cards - struct which contains information about cards, points to cards_t
 * @param settings - struct which contains information about settings, points to setting_t
 * @param players - number of players
*/
void Action(Runtime* runtime, Player player[], Cards cards[], Settings* settings, int players);

/**
 * Perform action on the top card.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param player - struct which contains information about player, points to player_t
 * @param cards - struct which contains information about cards, points to cards_t
 * @param players - number of players
*/
void TopCardAction(Runtime* runtime, Player player[], Cards cards[], Settings* settings, int players);

/**
 * Perform an action on the card which AI wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_t
 * @param player - struct which contains information about player, points to player_t
 * @param cards - struct which contains information about cards, points to cards_t
 * @param settings - struct which contains information about settings, points to setting_t
 * @param players - number of players 
*/
void AIAction(Runtime* runtime, Player player[], Cards cards[], Settings* settings, int players);

/**
 * Read or write points to text file.
 * @param points - struct for holding information about points, points to points_t
 * @param settings - struct which contains information about settings, points to setting_t
 * @param write - perform read of write
 * @param players - number of players
 * @param point - points, see function code in gameplay.c for naming convention
*/
int PointsFromFile(Points* points, Settings* settings, bool write, int player, int point);

/**
 * Assigning points and determining winner of the match.
 * @param player - struct which contains information about player, points to player_t
 * @param settings - struct which contains information about settings, points to setting_t
 * @param points - struct for holding information about points, points to points_t
 * @param players - number of players
*/
void PointsManager(Player player[], Settings* settings, Points* points, int players);

/**
 * Entry point for gameplay mechanics, calls all other functions in gameplay.h and gameplay.c.
 * @param settings - struct which contains information about settings, points to setting_t
 * @param points - struct for holding information about points, points to points_t
 * @param theme - struct for holding graphics (theme releated stuff mostly) informations during runtime, points to theme_t 
*/
void Gameplay(Settings* settings, Points* points, Theme* theme);
