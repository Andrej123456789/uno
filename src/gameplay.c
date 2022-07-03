#include "include/gameplay.h"

int ifFinished(int players)
{
    struct player_t player[players];

    for (int i = 0; i < players; i++)
    {
        if (player[i].number_of_cards == 0)
        {
            return 1;
        }

        else
        {
            return 0;
        }
    }
}

void Gameplay(int players)
{
    SetCards(players);
}

void SetCards(int players)
{
    time_t t;

    struct cards_t cards[109];
    struct player_t player[players];
    struct runtime_t runtime;

    int card_id = 1;
    int player_id = 1;
    player->number_of_cards = 0;
    runtime.avabible_cards = 108;

    srand((unsigned) time(&t));

    cards[0].number = 0;
    cards[0].color = 0;

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
    
    if (settings.debug_mode == 1)
    {
        printf("Cards: \n");

        for (int i = 0; i < 108; i++)
        {
            printf("\tNumber: %d, Color: %d\n", cards[i].number, cards[i].color);
        }
    }

    for (int i = 0; i < players; i++)
    {
        for (int j = 1; j < 8; j++)
        {
            player[i].cards[j] = cards[rand() % (109 - 1 + 1) + 1];
            printf("Player %d card id: %d, Number: %d, Color: %d\n", i, j, player[i].cards[j].number, player[i].cards[j].color);
            player[i].number_of_cards++;
        }
        runtime.avabible_cards -= 7;
        printf("\n");
    }

    runtime.top_card[0] = cards[rand() % (runtime.avabible_cards - 1 + 1) + 1];
    runtime.avabible_cards--;
    printf("Top card: Number: %d, Color: %d\n", runtime.top_card[0].number, runtime.top_card[0].color);

    if (settings.debug_mode == 1)
    {
        printf("[DEBUG] Avabible cards: %d\n", runtime.avabible_cards);
    }
}

void Play(int players)
{

}