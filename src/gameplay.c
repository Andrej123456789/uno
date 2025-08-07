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

#include "include/gameplay.h"
#include "include/strings.h"

bool isCompatible(Cards top_card, Cards players_card)
{
    if ((top_card.number == players_card.number) || (players_card.number >= WILD_CARD))
    {
        return true;
    }

    else if ((top_card.color == players_card.color) || (players_card.color == 0))
    {
        return true;
    }

    return false;
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

    /* Swap card */
    if (tweaks->swap_card == true)
    {
        temp.number = SWAP_CARD;
        temp.color = NO_COLOR;
         
        cvector_push_back(cards, temp);
    }

    return cards;
}

void Swap(Player src, Player dest)
{
    cvector_vector_type(Cards) temp = src.cards;
    src.cards = dest.cards;
    dest.cards = temp;
}

void NextPlayer(Runtime* runtime)
{
    if (runtime->isPositive == true)
    {
        if (runtime->current_player + 1 >= runtime->number_of_players)
        {
            runtime->current_player = 0;
        }

        else
        {
            runtime->current_player++;
        }
    }

    else
    {
        if (runtime->current_player - 1 < 0)
        {
            runtime->current_player = runtime->number_of_players - 1;
        }

        else
        {
            runtime->current_player--;
        }
    }
}

void Action(Runtime* runtime, Tweaks* tweaks, cvector_vector_type(Cards) cards, Cards card)
{
    (void)(runtime);
    (void)(tweaks);
    (void)(cards);
    (void)(card);
}

void PointsManager(Runtime* runtime, Points* points, Player* players)
{
    (void)(runtime);
    (void)(points);
    (void)(players);
}

void Gameplay(Runtime* runtime, Tweaks* tweaks, Points* points)
{
    char user_input[20];
    
    time_t t;
    srand((unsigned) time(&t));
    
    Player* players = calloc(runtime->number_of_players, sizeof(Player));
    cvector_vector_type(Cards) cards = GenerateDeck(tweaks);

    /* Deal the cards to players */
    size_t available_cards = cvector_size(cards);
    for (int i = 0; i < runtime->number_of_players; i++)
    {
        if (available_cards < 7)
        {
            cards = GenerateDeck(tweaks);
        }

        for (int j = 0; j < 7; j++)
        {
            size_t random = (rand() % ((available_cards) - 0 - 1)) + 0 + 1;
            cvector_push_back(players[i].cards, cards[random]);

            cvector_erase(cards, random);
            available_cards--;
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
    size_t random = (rand() % ((available_cards - 1) - 3 - 1)) + 3 + 1; // <0, 3>
    runtime->top_card = cards[random];

    cvector_erase(cards, random);
    available_cards--;

    Action(runtime, tweaks, cards, runtime->top_card);

    bool game_loop = true;
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

                size_t random = (rand() % ((available_cards - 1) - 3 - 1)) + 3 + 1; // <0, 3>
                cvector_push_back(players[runtime->current_player].cards, cards[random]);

                printf((tweaks->colors == true) ? new_card_color : new_card,
                       cards[random].number, cards[random].color);

                cvector_erase(cards, random);
                available_cards--;

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
                NextPlayer(runtime);
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

                Action(runtime, tweaks, cards, players[runtime->current_player].cards[card_id]);

                /* Check if player won */
                if (cvector_size(players[runtime->current_player].cards) == 0)
                {
                    game_loop = false;
                }

                runtime->top_card = players[runtime->current_player].cards[card_id];
                cvector_erase(players[runtime->current_player].cards, card_id);

                NextPlayer(runtime);
                break;
            }
        } while (true);
    }

    /* Write points */
    PointsManager(runtime, points, players);

    /* FREE */
    free(players);
    cvector_free(cards);
}
