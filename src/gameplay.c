#include "include/gameplay.h"
#include "include/setup.h"

void Gameplay(int players)
{
    SetCards(players);
}

void SetCards(int players)
{
    time_t t;

    struct cards_t cards[108];
    struct player_t player[players];

    int card_id = 1;
    int player_id = 1;

    srand((unsigned) time(&t));

    /* Wild card */
    for (int i = 0; i < 4; i++)
    {
        cards[card_id].number = 13;
        cards[card_id].color = 0;
        card_id++;
    }

    /* Wild draw four card */
    for (int i = 0; i < 4; i++)
    {
        cards[card_id].number = 14;
        cards[card_id].color = 0;
        card_id++;
    }

    /* Zero cards */
    for (int i = 1; i < 5; i++)
    {
        cards[card_id].number = 0;
        cards[card_id].color = i;
        card_id++;
    }

    /* Red color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 1;
        card_id++;
    }

    /* Yellow color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 2;
        card_id++;
    }

    /* Green color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 3;
        card_id++;
    }

    /* Blue color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 4;
        card_id++;
    }

    /* Red color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 1;
        card_id++;
    }

    /* Yellow color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 2;
        card_id++;
    }

    /* Green color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 3;
        card_id++;
    }

    /* Blue color */
    for (int i = 1; i < 13; i++)
    {
        cards[card_id].number = i;
        cards[card_id].color = 4;
        card_id++;
    }
    
    if (set.debug_mode == 1)
    {
        printf("Cards: \n");

        for (int i = 0; i < 108; i++)
        {
            printf("\tNumber: %d, Color: %d\n", cards[i].number, cards[i].color);
        }
    }

    for (int i = 0; i < players; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            player[j].cards[j] = cards[rand() % 107];
            printf("Player %d card id: %d, Number: %d, Color: %d\n", i, j, player[j].cards[j].number, player[j].cards[j].color);
        }
        printf("\n");
    }
}