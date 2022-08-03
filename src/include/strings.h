/**
 * @author Andrej123456789 (Andrej Bartulin)
 * @project uno++, simple game inspired by Uno in terminal
 * @license Apache License 2.0
 * @description strings.h, strings in the game
*/

#pragma once

#include "ANSI.h"

static const char enter_color[] = "Enter color [1 - red; 2 -  yellow; 3 - green; 4 - blue]: ";
static const char enter_color_color[] = "Enter color [\x1b[31m1 - red; \x1b[33m2 -  yellow; \x1b[32m3 - green; \x1b[34m4 - blue]: \x1b[0m";

static const char top_card[] = "Top card: Number: %d, Color: %d\n";
static const char top_card_color[] = "Top card: Number: \x1b[36m%d\x1b[0m, Color: \x1b[31m%d\n\x1b[0m";

static const char card_info[] = "Card id: %d, Number: %d, Color: %d\n";
static const char card_info_color[] = "Card id: \x1b[32m%d\x1b[0m, Number: \x1b[36m%d,\x1b[0m Color: \x1b[31m%d\n\x1b[0m";

static const char player_card_info[] = "Player %d card id: %d, Number: %d, Color: %d\n";
static const char player_card_info_color[] = "Player \x1b[35m%d\x1b[0m card id: \x1b[32m%d\x1b[0m, Number: \x1b[36m%d\x1b[0m, Color: \x1b[31m%d\n\x1b[0m";

static const char all_cards[] = "\tNumber: %d, Color: %d\n";
static const char all_cards_color[] = "\tNumber: \x1b[32m%d\x1b[0m, Color: \x1b[31m%d\n\x1b[0m";

static const char new_card[] = "Your new card is: Number: %d, Color: %d\n";
static const char new_card_color[] = "Your new card is: Number: %d, Color: %d\n";

static const char option[] = "Enter card id or do something else ['new' - take card from deck, 'all' - show all player's cards]: ";
static const char option_color[] = "Enter card id or do something else ['\x1b[36mnew\x1b[0m' - take card from deck, '\x1b[31mall\x1b[0m' - show all player's cards]: \x1b[0m";

static const char player_turn[] = "Player %d turn\n";
static const char player_turn_color[] = "Player \x1b[35m%d\x1b[0m turn\n";

static const char game_finished[] = "Game finished!\n";
static const char game_finished_color[] = "\x1b[32mGame finished!\n\x1b[0m";

static const char won_match[] = "Player %d won the match!\n";
static const char won_match_color[] = "\x1b[32mPlayer \x1b[35m%d\x1b[32m won the match!\n\x1b[0m";

static const char won_round[] = "Player %d won the round!\n";
static const char won_round_color[] = "\x1b[32mPlayer \x1b[35m%d\x1b[32m won the round!\n\x1b[0m";

static const char points[] = "Points: %d\n";
static const char points_color[] = "Points: \x1b[35m%d\x1b[0m\n";

static const char exiting[] = "Exiting...\n";
static const char exiting_color[] = "\x1b[31mExiting...\n\x1b[0m";

static const char card_not_compatible[] = "Card is not compatible!\n";
static const char card_not_compatible_color[] = "\x1b[31mCard is not compatible!\n\x1b[0m";

static const char ai_action[] = "\nAI action\n\n";
static const char ai_action_color[] = "\n\x1b[32mAI action\n\n\x1b[0m";
