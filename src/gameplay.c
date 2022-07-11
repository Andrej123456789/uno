#include "include/gameplay.h"
#include "include/strings.h"

bool isFinished(int players, struct player_t player[])
{
    int i;
    for (i = 0; i < players + 1; i++)
    {
        if (player[i].number_of_cards == 0)
        {
            return true;
        }
    }
    return false;
}

bool isCompatible(struct runtime_t* runtime, struct player_t player_card[])
{
    if (runtime->top_card->number == player_card[runtime->player_turn].cards[runtime->current_card_id].number | player_card[runtime->player_turn].cards[runtime->current_card_id].number > 12)
    {
        return true;
    }

	else if (runtime->top_card->color == player_card[runtime->player_turn].cards[runtime->current_card_id].color | player_card[runtime->player_turn].cards[runtime->current_card_id].number > 12)
    {
        return true;
    }

    else
    {
        return false;
    }
}

void Swap(struct runtime_t* runtime, struct player_t player[], int players, int swap_id)
{
    struct player_t a = player[runtime->player_turn];
    struct player_t b = player[swap_id];
    struct player_t temp;

    /* swap cards between players, a array is current player, b array is swap player */
    temp = a;
    a = b;
    b = temp;
}

void NextPlayer(struct runtime_t *runtime, int players, bool isPositive)
{
    if (isPositive == true)
    {
        if (runtime->player_turn + 1 != players)
        {
            runtime->player_turn++;
        }

        else
        {
            runtime->player_turn = 0;
        }
    }

    else
    {
        if (runtime->player_turn - 1 < 0)
        {
            runtime->player_turn++;
        }

        else
        {
            runtime->player_turn--;
        }
    }
}

void Action(struct runtime_t *runtime, struct player_t player[], struct cards_t cards[], struct setting_t* settings, int players)
{
    bool can_do_4 = false;

    char input[6];
    int temp_color;
    int temp_player;

    int number = player[runtime->player_turn].cards[runtime->current_card_id].number;
    int color = player[runtime->player_turn].cards[runtime->current_card_id].color;

    if (number == 0 | number < 10)
    {
        player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
        player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
        player->number_of_cards--;
    }

    else
    {
        switch (number) 
        {
            case 10:
                player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;
                player->number_of_cards++;

                player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;
                player->number_of_cards++;

                runtime->top_card[0].number = 0;
                runtime->top_card[0].color = 0;
                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, players, isPositive);
                NextPlayer(runtime, players, isPositive);

                return;
                break;

            case 11:
                if (isPositive == true)
                    isPositive = false;
                else
                    isPositive = true;

                NextPlayer(runtime, players, isPositive);

                return;
                break;

            case 12:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;
		
                NextPlayer(runtime, players, isPositive);
                NextPlayer(runtime, players, isPositive);

                return;
                break;

            case 13:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                printf("%s", (settings->colors == 1) ? enter_color_color : enter_color);
                scanf("%s", input);
                temp_color = atoi(input);

                runtime->top_card[0].number = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1].number;
                runtime->top_card[0].color = temp_color;
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, players, isPositive);

                return;
                break;

            case 14:
                for (int i = 0; i < player->number_of_cards + 1; i++)
                {
                    if (player[runtime->player_turn].cards[i].color != runtime->top_card[0].color)
                    {
                        can_do_4 = true;
                    }
                }

                if (can_do_4 == true)
                {
                    player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                    player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                    player->number_of_cards--;
                    
                    player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;
                    player->number_of_cards++;

                    player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;
                    player->number_of_cards++;

                    player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;
                    player->number_of_cards++;

                    player[runtime->player_turn + 1].cards[player[runtime->player_turn + 1].number_of_cards + 1] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;
                    player->number_of_cards++;

                    runtime->top_card[0].number = 0;
                    runtime->top_card[0].color = 0;
                    runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;

                    printf("\t -------------------- \t \n");
                    printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                    printf("\t -------------------- \t \n");

                    NextPlayer(runtime, players, isPositive);
                    NextPlayer(runtime, players, isPositive);
                }

            return;
            break;

            case 15:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                printf("Enter player number: ");
                scanf("%s", input);
                temp_player = atoi(input);
                Swap(runtime, player, players, temp_player);

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, players, isPositive);

                return;
                break;

            default:
                return;
                break;
        }
    }

    runtime->top_card[0].number = 0;
    runtime->top_card[0].color = 0;
    runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
    runtime->avabible_cards--;

    printf("\t -------------------- \t \n");
    printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
    printf("\t -------------------- \t \n");

    NextPlayer(runtime, players, isPositive);
}

void TopCardAction(struct runtime_t *runtime, struct player_t player[], struct cards_t cards[], int players)
{
    int number = runtime->top_card[0].number;

	if (number == 0 | number < 10)
	{
		return;
	}

	else
	{
		switch (number) 
		{
			case 10:
                player[0].cards[++player->number_of_cards] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                player[0].cards[++player->number_of_cards] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                break;

            case 11:
                if (isPositive == true)
                    isPositive = false;
                else
                    isPositive = true;

                NextPlayer(runtime, players, isPositive);
                break;

            case 12:
                NextPlayer(runtime, players, isPositive);
                NextPlayer(runtime, players, isPositive);
                break;

            case 13:
                runtime->top_card[0].color = cards[rand() % (4 - 1 + 1) + 1].color;
                break;

            default:
                break;
		}
	}	
}

void Gameplay(struct setting_t* settings, int players)
{
    char tmp_input[20];
    time_t t;

    struct cards_t cards[109];
    struct player_t player[players];
    struct runtime_t *runtime = malloc(sizeof(struct runtime_t));

    int card_id = 1;
    int player_id = 1;
    player->number_of_cards = 0;
    runtime->current_card_id = 0;
    runtime->player_turn = 0;

    srand((unsigned) time(&t));

    if (settings->swap_card == 1)
    {
        cards[0].number = 15;
        cards[0].color = 0;

        runtime->avabible_cards = 109;
    }

    else
    {
        cards[0].number = 0;
        cards[0].color = 0;

        runtime->avabible_cards = 108;
    }

    /* Wild card */
    for (int i = 0; i < 4; i++)
    {
        cards[card_id].number = 14;
        cards[card_id].color = 0;
        card_id++;
    }

    /* Wild draw four card */
    for (int i = 0; i < 4; i++)
    {
        cards[card_id].number = 13;
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
    
    if (settings->debug_mode == 1)
    {
        printf("Cards: \n");

        for (int i = 0; i < runtime->avabible_cards; i++)
        {
            printf((settings->colors == 1) ? all_cards_color : all_cards, cards[i].number, cards[i].color);
        }
    }

    for (int i = 0; i < players; i++)
    {
        for (int j = 1; j < 8; j++)
        {   if (settings->swap_card == 1)
                player[i].cards[j] = cards[rand() % (109 - 0 + 0) + 0];
            else
                player[i].cards[j] = cards[rand() % (109 - 1 + 1) + 1];
            printf((settings->colors == 1) ? player_card_info_color : player_card_info, i, j, player[i].cards[j].number, player[i].cards[j].color);
            player[i].number_of_cards++;
        }
        runtime->avabible_cards -= 7;
        printf("\n");
    }

    runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 5 + 5) + 5];
    runtime->avabible_cards--;

    printf("\t -------------------- \t \n");
    printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
    printf("\t -------------------- \t \n");

    TopCardAction(runtime, player, cards, players);

    if (settings->debug_mode == 1)
    {
        printf("[DEBUG] Avabible cards: %d\n", runtime->avabible_cards);
    }

    while (true)
    {
        if (isFinished(players, player) == true)
        {
            printf((settings->colors == 1) ? game_finished_color : game_finished);
            free(runtime);
            break;
        }

        again:
        printf((settings->colors == 1) ? player_turn_color : player_turn, runtime->player_turn);
        try_again:
        printf((settings->colors == 1) ? option_color : option, runtime->player_turn);
        scanf("%s", &tmp_input);

        if (strcmp(tmp_input, "new") == 0)
        {
            if (settings->swap_card == 1)
                player[runtime->player_turn].cards[++player->number_of_cards] = cards[rand() % (runtime->avabible_cards - 0 + 0) + 0];
            else
                player[runtime->player_turn].cards[++player->number_of_cards] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
            runtime->avabible_cards--;
            printf((settings->colors == 1) ? new_card_color : new_card, player[runtime->player_turn].cards[player->number_of_cards].number, 
                                                                player[runtime->player_turn].cards[player->number_of_cards].color);
            goto try_again;
        }

		else if (strcmp(tmp_input, "all") == 0)
		{
			for (int i = 1; i < player->number_of_cards + 1; i++)
			{
				printf((settings->colors == 1) ? card_info_color : card_info_color, i, player[runtime->player_turn].cards[i].number, 
                                                                    player[runtime->player_turn].cards[i].color);
			}
			goto try_again;
		}

        else if (strcmp(tmp_input, "exit") == 0)
        {
            printf((settings->colors == 1) ? exiting_color : exiting);
            free(runtime);
            break;
        }

        else
        {
            runtime->current_card_id = atoi(tmp_input);
        }

        if (isCompatible(runtime, player))
        {
            /* take new top card and go to other player */
            Action(runtime, player, cards, settings, players);

            if (settings->debug_mode == 1)
            {
                printf("[DEBUG] Avabible cards: %d\n", runtime->avabible_cards);
            }
            goto again;
        }

        else
        {
            printf((settings->colors == 1) ? card_not_compatible_color : card_not_compatible);
            goto try_again;
        }
    }
}
