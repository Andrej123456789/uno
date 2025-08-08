/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++
 * LICENSE: MIT License
 * DESCRIPTION: Header file for gameplay mechanics
*/

#pragma once

#include <stdbool.h>
#include "c_vector.h"

/**
 * Enum for numbers of the card.
 */
enum Cards
{
    ZERO,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    PLUS_TWO,
    REVERSE_CARD,
    SKIP_CARD,
    WILD_CARD,
    WILD_DRAW,
    SWAP_CARD
};

/**
 * Enum for colors of the card.
 */
enum Colors
{
    NO_COLOR,
    RED,
    YELLOW,
    GREEN,
    BLUE
};

/**
 * Card's struct.
 * @param number number of the card
 * @param color - color of the card
*/
typedef struct cards_T
{
    short number;
    short color;
} Cards;

/**
 * Player's struct.
 * @param cards vector containing cards
*/
typedef struct player_T
{
    cvector_vector_type(Cards) cards;
} Player;

/**
 * Struct containing information related to storing points.
 * @param path path to the JSON file containing points
 * @param match_points number of points needed in order to win the game
 */
typedef struct points_T
{
    char path[257];
    int match_points;
} Points;

/**
 * Struct containing runtime information.
 * @param number_of_players number of players in the game
 * @param current_player id (array index) of the current player
 * @param isPositive direction of the next player
 * @param top_card top card
*/
typedef struct runtime_T
{
    int number_of_players;
    int current_player;
    bool isPositive;
    Cards top_card;

    /**
     * Struct related to stacking of +2 and +4 cards.
     * @param happening is stacking in progress
     * @param type +2 or +4 card
     * @param number_of_cards how many cards have been stacked
     */
    struct
    {
        bool happening;
        short type;
        int number_of_cards;
    } stacking;
} Runtime;

/**
 * Struct containing tweaks of the game.
 * @param colors are colors enabled
 * @param stacking allow stacking of +2 and +4 cards
 * @param swap_card is swap card enabled
 * @param seven_o is SevenO rule enabled
*/
typedef struct tweaks_T
{
    bool colors;
    bool stacking;
    bool swap_card;
    bool seven_o;
} Tweaks;

/* ------------------------------------------------------------------------ */

/**
 * Perform an action of the given card.
 * @param runtime struct containing runtime information
 * @param tweaks struct containing tweaks settings
 * @param players an array of players
 * @param cards cards in the deck
 * @param card card which will perform an action
 * @return void
*/
void Action(Runtime* runtime, Tweaks* tweaks, Player* players, cvector_vector_type(Cards) cards, Cards card);

/**
 * Generate a deck of cards.
 * @param tweaks struct containing tweaks settings
 * @return cvector_vector_type(Cards)
*/
cvector_vector_type(Cards) GenerateDeck(Tweaks* tweaks);

/**
 * Return points value of a card.
 * @param card card to be evaluated
 * @return int
 */
int GetValue(Cards card);

/**
 * Check if a card player wants to play is compatible with the top card.
 * @param top_card reference
 * @param players_card candidate
 * @return bool
*/
bool isCompatible(Cards top_card, Cards players_card);

/**
 * Switch turn to the next player.
 * @param runtime struct containing runtime information
 * @param execute set id (array index) to the next player
 * @return int
*/
int NextPlayer(Runtime* runtime, bool execute);

/**
 * Manage points.
 * @param runtime struct containing runtime information
 * @param tweaks struct containing tweaks settings
 * @param points struct containing information related to storing points
 * @param players an array of players
 * @return void
 */
void PointsManager(Runtime* runtime, Tweaks* tweaks, Points* points, Player* players);

/**
 * Swap cards between two players.
 * @param src source
 * @param dest destination
 * @return void
*/
void Swap(Player* src, Player* dest);

/* ----------------------------------------------------- */

/**
 * Entry point for gameplay.
 * @param runtime struct containing runtime information
 * @param tweaks struct containing tweaks settings
 * @param points struct containing information related to storing points
 * @return void
*/
void Gameplay(Runtime* runtime, Tweaks* tweaks, Points* points);
