/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++
 * LICENSE: MIT License
 * DESCRIPTION: gameplay.c, C file for gameplay mechanics
*/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <json-c/json.h>

#include "include/gameplay.h"
#include "include/strings.h"

void Action(Runtime* runtime, Tweaks* tweaks, Player* players, cvector_vector_type(Cards)* cards, Cards card)
{
    int color = 0;
    int doubt = -1;
    int next_player = -1;
    int player = -1;

    switch (card.number)
    {
        case ZERO:
            if (tweaks->seven_o == true)
            {
                if (runtime->isPositive == true)
                {
                    cvector_vector_type(Cards) temp = players[runtime->number_of_players - 1].cards;
                    for (int i = runtime->number_of_players - 1; i > 0; i--)
                    {
                        players[i].cards = players[i - 1].cards;
                    }

                    players[0].cards = temp;
                }

                else
                {
                    cvector_vector_type(Cards) temp = players[0].cards;
                    for (int i = 0; i < runtime->number_of_players - 1; i++)
                    {
                        players[i].cards = players[i + 1].cards;
                    }

                    players[runtime->number_of_players - 1].cards = temp;
                }   
            }

            break;

        case SEVEN:
            if (tweaks->seven_o == true)
            {
                printf("\nEnter player's number with whom you want to swap cards: ");
                scanf("%d", &player);

                if (player < 0 || player >= runtime->number_of_players)
                {
                    player = !runtime->current_player;
                    printf("Invalid player! Defaulting to %d\n", player);
                }

                else
                {
                    break;
                }

                Swap(&players[runtime->current_player], &players[player]);
            }

            break;

        case PLUS_TWO:
            next_player = NextPlayer(runtime, false);

            for (int i = 0; i < 2; i++)
            {
                size_t random = GetRandomCard(cards, tweaks);

                cvector_push_back(players[next_player].cards, (*cards)[random]);
                cvector_erase(*cards, random);
            }
            NextPlayer(runtime, true);

            /* add stacking */
            
            break;

        case REVERSE_CARD:
            runtime->isPositive = !runtime->isPositive;
            break;

        case SKIP_CARD:
            NextPlayer(runtime, true);
            break;

        case WILD_CARD:
            printf((tweaks->colors == true) ? enter_color_color : enter_color);
            scanf("%d", &color);

            if (color < 1 || color > 4)
            {
                printf((tweaks->colors == true) ? invalid_color_color : invalid_color);
                color = 1;
            }

            runtime->top_card.color = color;
            break;

        case WILD_DRAW:
            int player_to_draw = NextPlayer(runtime, false);
            int number_of_cards_to_draw = 4;
            
            /* Get color */
            printf((tweaks->colors == true) ? enter_color_color : enter_color);
            scanf("%d", &color);

            if (color < 1 || color > 4)
            {
                printf((tweaks->colors == true) ? invalid_color_color : invalid_color);
                color = 1;
            }
            runtime->top_card.color = color;

            /* Doubt */
            if (tweaks->stacking == false)
            {
                printf("Player %d, are you doubting? (0 - no, 1 - yes) ", player_to_draw);
                scanf("%d", &doubt);

                if (doubt != 1)
                {
                    printf("Not doubting!\n");
                }

                else
                {
                    bool match = false;
                    for (size_t i = 0; i < cvector_size(players[runtime->current_player].cards); i++)
                    {
                        if (players[runtime->current_player].cards[i].color == runtime->previous_top_card.color)
                        {
                            match = true;
                            break;
                        }
                    }

                    if (match == true)
                    {
                        printf("Doubt was correct!\n");
                        player_to_draw = runtime->current_player;
                    }

                    else
                    {
                        printf("Doubt was incorrect!\n");
                        number_of_cards_to_draw = 6;
                    }
                    
                }
            }

            /* Draw cards */
            for (int i = 0; i < number_of_cards_to_draw; i++)
            {
                size_t random = GetRandomCard(cards, tweaks);

                cvector_push_back(players[player_to_draw].cards, (*cards)[random]);
                cvector_erase(*cards, random);
            }

            NextPlayer(runtime, true);

            /* add stacking */

            break;

        case SWAP_CARD:
            printf((tweaks->colors == true) ? enter_color_color : enter_color);
            scanf("%d", &color);

            if (color < 1 || color > 4)
            {
                printf((tweaks->colors == true) ? invalid_color_color : invalid_color);
                color = 1;
            }
            runtime->top_card.color = color;

            printf("\nEnter player's number with whom you want to swap cards: ");

            if (player < 0 || player >= runtime->number_of_players)
            {
                player = !runtime->current_player;
                printf("Invalid player! Defaulting to %d\n", player);
            }

            else
            {
                break;
            }

            Swap(&players[runtime->current_player], &players[player]);
            break;
        
        default:
            break;
    }
}

cvector_vector_type(Cards) GenerateDeck(Tweaks* tweaks)
{
    cvector_vector_type(Cards) cards = NULL;
    Cards temp;

    /* Wild draw four cards */
    for (int i = 0; i < 4; i++)
    {
        temp.number = WILD_DRAW;
        temp.color = NO_COLOR;

        cvector_push_back(cards, temp);
    }

    /* Swap card */
    if (tweaks->swap_card == true)
    {
        temp.number = SWAP_CARD;
        temp.color = NO_COLOR;

        cvector_push_back(cards, temp);
    }

    /* Wild cards */
    for (int i = 0; i < 4; i++)
    {
        temp.number = WILD_CARD;
        temp.color = NO_COLOR;

        cvector_push_back(cards, temp);
    }

    /* Zero cards */
    for (int i = RED; i < BLUE + 1; i++)
    {
        temp.number = ZERO;
        temp.color = i;

        cvector_push_back(cards, temp);
    }

    /* 1 - skip card */
    for (int i = 0; i < 2; i++)
    {
        for (int j = RED; j < BLUE + 1; j++)
        {
            for (int k = ONE; k < WILD_CARD; k++)
            {
                temp.number = k;
                temp.color = j;

                cvector_push_back(cards, temp);
            }
        }
    }

    return cards;
}

size_t GetRandomCard(cvector_vector_type(Cards)* cards, Tweaks* tweaks)
{
    size_t size = cvector_size(*cards);
    if (size == 0)
    {
        cvector_free(*cards);

        *cards = GenerateDeck(tweaks);
        size = cvector_size(*cards);
    }

    return rand() % size;
}

int GetValue(Cards card)
{
    if (card.number >= 0 && card.number <= 9)
    {
        return card.number;
    }

    else if (card.number >= PLUS_TWO && card.number <= SKIP_CARD)
    {
        return 20;
    }

    else if (card.number >= WILD_CARD && card.number <= WILD_DRAW)
    {
        return 50;
    }

    else if (card.number >= SWAP_CARD)
    {
        return 40;
    }

    else
    {
        return 0;
    }
}

bool isCompatible(Cards top_card, Cards players_card)
{
    if (players_card.number >= WILD_CARD)
    {
        return true;
    }

    if ((top_card.number == players_card.number) || (top_card.color == players_card.color))
    {
        return true;
    }

    return false;
}

int NextPlayer(Runtime* runtime, bool execute)
{
    int player = runtime->current_player;

    if (runtime->isPositive == true)
    {
        if (runtime->current_player + 1 >= runtime->number_of_players)
        {
           player = 0;
        }

        else
        {
            player++;
        }
    }

    else
    {
        if (runtime->current_player - 1 < 0)
        {
            player = runtime->number_of_players - 1;
        }

        else
        {
            player--;
        }
    }

    if (execute == true)
    {
        runtime->current_player = player;
    }

    return player;
}

void PointsManager(Runtime* runtime, Tweaks* tweaks, Points* points, Player* players)
{
    printf((tweaks->colors == true) ? game_finished_color : game_finished);
    printf((tweaks->colors == true) ? won_round_color : won_round, runtime->current_player);

    /* Open JSON file */
    FILE *fp = fopen(points->path, "r");
    if (!fp)
    {
        perror("Failed to open file");
        return;
    }

    /* Read file into buffer */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char* buffer = malloc(fsize + 1);
    if (!buffer)
    {
        printf("Error during memory allocation!\n");
        fclose(fp);

        return;
    }

    fread(buffer, 1, fsize, fp);
    buffer[fsize] = '\0';
    fclose(fp);

    /* Parse JSON */
    struct json_object* root = json_tokener_parse(buffer);
    free(buffer);

    if (!root)
    {
        printf("Error parsing JSON!\n");
        return;
    }

    /* Get player number */
    int player_num = runtime->current_player;

    /* Get points */
    int add_points = 0;
    for (int i = 0; i < runtime->number_of_players; i++)
    {
        if (i == runtime->current_player)
        {
            continue;
        }

        for (size_t j = 0; j < cvector_size(players[i].cards); j++)
        {
            add_points += GetValue(players[i].cards[j]);
        }
    }

    /* Build key string: "Player X" */
    char player_key[32];
    snprintf(player_key, sizeof(player_key), "Player %d", player_num);

    /* Get or create player entry */
    struct json_object* player_score;
    if (json_object_object_get_ex(root, player_key, &player_score))
    {
        /* Update in place */
        int current_points = json_object_get_int(player_score);
        json_object_set_int(player_score, current_points + add_points);

        if ((current_points + add_points) >= points->match_points)
        {
            printf((tweaks->colors == true) ? won_match_color : won_match, runtime->current_player);
        }
    }

    else
    {
        /* Create new entry */
        json_object_object_add(root, player_key, json_object_new_int(add_points));
    }

    /* Write updated JSON back to file */
    fp = fopen(points->path, "w");
    if (!fp)
    {
        printf("Failed to open file for writing!\n");
        json_object_put(root);

        return;
    }

    fprintf(fp, "%s\n", json_object_to_json_string(root));
    fclose(fp);

    json_object_put(root);
}

void Swap(Player* src, Player* dest)
{
    cvector_vector_type(Cards) temp = src->cards;
    src->cards = dest->cards;
    dest->cards = temp;
}

/* ----------------------------------------------------- */

void Gameplay(Runtime* runtime, Tweaks* tweaks, Points* points)
{
    char user_input[20];
    
    time_t t;
    srand((unsigned) time(&t));
    
    Player* players = calloc(runtime->number_of_players, sizeof(Player));
    cvector_vector_type(Cards) cards = GenerateDeck(tweaks);

    /* Deal the cards to players */
    for (int i = 0; i < runtime->number_of_players; i++)
    {
        for (int j = 0; j < 7; j++)
        {
            size_t random = GetRandomCard(&cards, tweaks);
            cvector_push_back(players[i].cards, cards[random]);

            cvector_erase(cards, random);
        }

        if (players[i].cards) 
        {
            for (size_t z = 0; z < 7; z++) 
            {
                printf((tweaks->colors == true) ? player_card_info_color : player_card_info,
                       i, z, players[i].cards[z].number, players[i].cards[z].color);
            }
        }

        printf("\n");
    }

    /* Top card */
    if (cvector_size(cards) == 0)
    {
        cvector_free(cards);
        cards = GenerateDeck(tweaks);
    }

    size_t start = (tweaks->swap_card == true) ? 5 : 4;
    size_t random = start + rand() % (cvector_size(cards) - start);

    runtime->top_card = cards[random];
    cvector_erase(cards, random);

    Action(runtime, tweaks, players, &cards, runtime->top_card);

    bool game_loop = true;
    bool round_ended = false;

    while (game_loop)
    {
        /* Check if the deck is empty */
        if (cvector_size(cards) == 0)
        {
            cards = GenerateDeck(tweaks);
        }

        bool alReadyNew = false;
        int card_id = -1;

        printf("\t -------------------- \t \n");
        printf((tweaks->colors == true) ? top_card_color : top_card, runtime->top_card.number, runtime->top_card.color);
        printf("\t -------------------- \t \n");

        printf((tweaks->colors == true) ? player_turn_color : player_turn, runtime->current_player);

        do
        {
            printf((tweaks->colors == true) ? option_color : option_text);
            scanf("%20s", user_input);

            if (strcmp(user_input, "new") == 0)
            {
                if (alReadyNew == true)
                {
                    printf((tweaks->colors == 1) ? discard_or_play_color : discard_or_play);
                    continue;
                }

                size_t random = GetRandomCard(&cards, tweaks);
                cvector_push_back(players[runtime->current_player].cards, cards[random]);

                printf((tweaks->colors == true) ? new_card_color : new_card,
                       cards[random].number, cards[random].color);

                cvector_erase(cards, random);
                alReadyNew = true;
            }

            else if (strcmp(user_input, "all") == 0)
            {
                if (players[runtime->current_player].cards)
                {
                    for (size_t i = 0; i < cvector_size(players[runtime->current_player].cards); i++)
                    {
                        printf((tweaks->colors == true) ? card_info_color : card_info,
                               i, players[runtime->current_player].cards[i].number,
                               players[runtime->current_player].cards[i].color);
                    }
                }
            }

            else if (strcmp(user_input, "discard") == 0)
            {
                NextPlayer(runtime, true);
                break;
            }

            else if (strcmp(user_input, "exit") == 0)
            {
                printf((tweaks->colors == true) ? exiting_color : exiting);

                game_loop = false;
                break;
            }

            else
            {
                card_id = atoi(user_input);
                if (card_id < 0 || (size_t)card_id >= cvector_size(players[runtime->current_player].cards))
                {
                    printf((tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    continue;
                }

                if (!isCompatible(runtime->top_card, players[runtime->current_player].cards[card_id]))
                {
                    printf((tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    continue;
                }

                runtime->previous_top_card = runtime->top_card;
                runtime->top_card = players[runtime->current_player].cards[card_id];
                cvector_erase(players[runtime->current_player].cards, card_id);

                Action(runtime, tweaks, players, &cards, runtime->top_card);

                /* Check if player won */
                if (cvector_size(players[runtime->current_player].cards) == 0)
                {
                    game_loop = false;
                    round_ended = true;
                }

                NextPlayer(runtime, true);
                break;
            }
        } while (true);
    }

    /* Write points */
    if (round_ended == true)
    {
        PointsManager(runtime, tweaks, points, players);
    }

    /* Free everything up */
    for (int i = 0; i < runtime->number_of_players; i++)
    {
        cvector_free(players[i].cards);
    }

    free(players);
    cvector_free(cards);
}
