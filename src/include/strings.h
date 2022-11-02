/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: ringwormGO General License 1.0 | (RGL) 2022
 * DESCRIPTION: strings.h, strings in the game
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

static const char option_text[] = "Enter card id or do something else ['new' - take card from deck, 'all' - show all player's cards]: ";
static const char option_color[] = "Enter card id or do something else ['\x1b[36mnew\x1b[0m' - take card from deck, '\x1b[31mall\x1b[0m' - show all player's cards]: \x1b[0m";

static const char player_turn[] = "Player %d turn\n";
static const char player_turn_color[] = "Player \x1b[35m%d\x1b[0m turn\n";

static const char game_finished[] = "Game finished!\n";
static const char game_finished_color[] = "\x1b[32mGame finished!\n\x1b[0m";

static const char won_match[] = "Player %d won the match!\n";
static const char won_match_color[] = "\x1b[32mPlayer \x1b[35m%d\x1b[32m won the match!\n\x1b[0m";

static const char won_round[] = "Player %d won the round!\n";
static const char won_round_color[] = "\x1b[32mPlayer \x1b[35m%d\x1b[32m won the round!\n\x1b[0m";

static const char points_text[] = "Points: %d\n";
static const char points_color[] = "Points: \x1b[35m%d\x1b[0m\n";

static const char exiting[] = "Exiting...\n";
static const char exiting_color[] = "\x1b[31mExiting...\n\x1b[0m";

static const char card_not_compatible[] = "Card is not compatible!\n";
static const char card_not_compatible_color[] = "\x1b[31mCard is not compatible!\n\x1b[0m";

static const char ai_action[] = "\nAI action\n\n";
static const char ai_action_color[] = "\n\x1b[32mAI action\n\n\x1b[0m";

static const char from_to_client[] = "From client: %sTo client: ";
static const char from_to_client_color[] = "\x1b[33mFrom client: \x1b[0m%s\x1b[31mTo client: \x1b[0m";

static const char discard_or_play[] = "You have already drawn a card from the deck, you can play a card or discard a turn!\n";
static const char discard_or_play_color[] = "\x1b[33mYou have already drawn a card from the deck, you can play a card or discard a turn!\n\x1b[0m";

static const char server_exiting[] = "Server exiting...\n";
static const char server_exiting_color[] = "\x1b[35mServer exiting...\n\x1b[0m";

static const char special_function_all[] = "[SPECIAL FUNCTION] Number of client connected to server is: %d\n";
static const char special_function_all_color[] = "\x1b[34m[SPECIAL FUNCTION] Number of client connected to server is: %d\x1b[0m\n";

static const char socket_creation_failed[] = "Socket creation failed!\nExiting...\n";
static const char socket_creation_failed_color[] = "\x1b[31mSocket creation failed!\nExiting...\n\x1b[0m";

static const char socket_bind_failed[] = "Socket bind failed!\nExiting...\n";
static const char socket_bind_failed_color[] = "\x1b[31mSocket bind failed!\nExiting...\n\x1b[0m";

static const char listen_failed[] = "Listen failed!\nExiting...\n";
static const char listen_failed_color[] = "\x1b[31m[Listen failed!\nExiting...\n\x1b[0m";

static const char failed_to_accept_client[] = "Socket failed to accept client!\nExiting...\n";
static const char failed_to_accept_client_color[] = "\x1b[31mSocket failed to accept server!\nExiting...\n\x1b[0m";

static const char socket_creation[] = "Socket successfully created...\n";
static const char socket_creation_color[] = "\x1b[32mSocket successfully created...\n\x1b[0m";

static const char socket_bind[] = "Socket successfully binded...\n";
static const char socket_bind_color[] = "\x1b[32mSocket successfully binded...\n\x1b[0m";

static const char server_listen[] = "Server listening...\n";
static const char server_listen_color[] = "\x1b[32mServer listening...\n\x1b[0m";

static const char accept_client[] = "Server has accepted client %d...\n"; 
static const char accept_client_color[] = "\x1b[32mServer has accepted client %d...\n\x1b[0m";
