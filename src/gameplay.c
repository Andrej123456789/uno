/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: gameplay.c, C file for gameplay mechanics
*/

#include "include/gameplay.h"
#include "include/util.h"

/**
 * Check if some player finished the round.
 * @param players - number of players
 * @param player - struct which contains information about player, points to player_T
 * @param points - struct for holding information about points, points to points_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
bool isFinished(Player player[], Points* points, Settings* settings)
{
    for (int i = 0; i < settings->players; i++)
    {
        if (player[i].number_of_cards == 0)
        {
            points->round_winner = i;
            return true;
        }
    }
    return false;
}

/**
 * Check if cards which player wants to play is compatible with the top card.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
*/
bool isCompatible(Runtime* runtime, Player players_card[])
{
    if ((runtime->top_card[0].number == players_card[runtime->player_turn].cards[runtime->current_card_id].number) | 
                                    (players_card[runtime->player_turn].cards[runtime->current_card_id].number > 12))
    {
        return true;
    }

    else if ((runtime->top_card[0].color == players_card[runtime->player_turn].cards[runtime->current_card_id].color) 
                                    | (players_card[runtime->player_turn].cards[runtime->current_card_id].number > 12))
    {
        return true;
    }

    else if (runtime->top_card[0].number == 0 && players_card[runtime->player_turn].cards[runtime->current_card_id].color == 
                                                runtime->top_card[0].color)
    {
        return true;
    }

    else
    {
        return false;
    }
}

/**
 * Generates a deck of cards
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void GenerateDeck(Runtime* runtime, Cards cards[], Settings* settings)
{
    int card_id = 1;

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
    for (int i = 0; i < 2; i++)
    {
        for (int i = 1; i < 13; i++)
        {
            cards[card_id].number = i;
            cards[card_id].color = 1;
            card_id++;
        }
    }

    /* Yellow color */
    for (int i = 0; i < 2; i++)
    {
        for (int i = 1; i < 13; i++)
        {
            cards[card_id].number = i;
            cards[card_id].color = 2;
            card_id++;
        }
    }

    /* Green color */
    for (int i = 0; i < 2; i++)
    {
        for (int i = 1; i < 13; i++)
        {
            cards[card_id].number = i;
            cards[card_id].color = 3;
            card_id++;
        }
    }

    /* Blue color */
    for (int i = 0; i < 2; i++)
    {
        for (int i = 1; i < 13; i++)
        {
            cards[card_id].number = i;
            cards[card_id].color = 4;
            card_id++;
        }
    }

    card_id = 1;
}

/**
 * Swap cards bettwen two players.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param swap_id - player which will got the cards from player which asked for swap
*/
void Swap(Runtime* runtime, Player player[], int swap_id)
{
    Player a = player[runtime->player_turn];
    Player b = player[swap_id];
    Player temp;

    /* swap cards between players, a array is current player, b array is swap player */
    temp = a;
    a = b;
    b = temp;
}

/**
 * Switch turn to the next player.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param players - number of players
 * @param doReturn - do return of next player turn 
*/
int NextPlayer(Runtime* runtime, Settings* settings, bool doReturn)
{
    int temp = runtime->player_turn;

    if (runtime->isPositive == true)
    {
        if (runtime->player_turn + 1 >= settings->players)
        {
            temp = 0;
        }

        else
        {
            temp++;
        }
    }

    else
    {
        if (runtime->player_turn - 1 < 0)
        {
            temp++;
        }

        else
        {
            temp--;
        }
    }

    if (doReturn)
    {
        return temp;
    }

    runtime->player_turn = temp;
    return -1;
}

/**
 * Perform action on the card which user wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void Action(Runtime* runtime, Player player[], Cards cards[], Settings* settings)
{
    char input[6];
    int temp_color;
    int temp_player;

    int number = player[runtime->player_turn].cards[runtime->current_card_id].number;

    if ((number == 0) | (number < 10))
    {
        player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
        player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
        player[runtime->player_turn].number_of_cards--;
    }

    else
    {
        int next = NextPlayer(runtime, settings, true);
        int num_cards = player[1].number_of_cards;
        switch (number) 
        {
            case 10:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player[runtime->player_turn].number_of_cards--;

                for (int i = 1; i < 3; i++)
                {
                    player[next].cards[num_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];

                    runtime->avabible_cards--;
                    player[next].number_of_cards++;

                    if (settings->debug_mode)
                    {
                        VectorPushBack(&player[runtime->player_turn].test, (void*)50);
                        printf("[DEBUG [TEST] ] Element test: %d\n", (int)VectorGet(&player[runtime->player_turn].test, 0));
                    }
                }

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

                return;
                break;

            case 11:
                if (runtime->isPositive == true)
                    runtime->isPositive = false;
                else
                    runtime->isPositive = true;

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);

                return;
                break;

            case 12:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");
		
                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

                return;
                break;

            case 13:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                printf("%s", (settings->colors == 1) ? enter_color_color : enter_color);
                scanf("%s", input);
                temp_color = atoi(input);

                runtime->top_card[0].number = 0;
                runtime->top_card[0].color = temp_color;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);

                return;
                break;

            case 14:
                for (int i = 0; i < player->number_of_cards + 1; i++)
                {
                    if (player[runtime->player_turn].cards[i].color != runtime->top_card[0].color)
                    {
                        player[runtime->player_turn].legal_four = true;
                    }

                    else
                    {
                        player[runtime->player_turn].legal_four = false;
                    }
                }

                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                for (int i = 1; i < 5; i++)
                {
                    player[next].cards[num_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];

                    runtime->avabible_cards--;
                    player[next].number_of_cards++;

                    if (settings->debug_mode)
                    {
                        VectorPushBack(&player[runtime->player_turn].test, (void*)50);
                        printf("[DEBUG [TEST] ] Element test: %d\n", (int)VectorGet(&player[runtime->player_turn].test, 0));
                    }
                }
                
                printf("%s", (settings->colors == 1) ? enter_color_color : enter_color);
                scanf("%s", input);
                temp_color = atoi(input);

                runtime->top_card[0].number = 0;
                runtime->top_card[0].color = temp_color;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

            return;
            break;

            case 15:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                printf("Enter player number: ");
                scanf("%s", input);
                temp_player = atoi(input);
                Swap(runtime, player, temp_player);

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);

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

    NextPlayer(runtime, settings, false);
}

/**
 * Perform action on the top card.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param startup - does this function runs at startup
*/
void TopCardAction(Runtime* runtime, Player player[], Cards cards[], Settings* settings)
{
    int number = runtime->top_card[0].number;

    if ((number == 0) | (number < 10))
    {
        return;
    }

    else
    {
        switch (number) 
        {
            case 10:
                for (int i = 1; i < 3; i++)
                {
                    player[0].cards[player[0].number_of_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                    runtime->avabible_cards--;
                }

                break;

            case 11:
                if (runtime->isPositive == true)
                    runtime->isPositive = false;
                else
                    runtime->isPositive = true;

                NextPlayer(runtime, settings, false);
                break;

            case 12:
                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);
                break;

            case 13:
                runtime->top_card[0].color = cards[rand() % (4 - 1 + 1) + 1].color;
                break;

            default:
                break;
        }
	}	
}

/**
 * Perform an action on the card which AI wants to play.
 * @param runtime - struct for holding information during the game, points to runtime_T
 * @param player - struct which contains information about player, points to player_T
 * @param cards - struct which contains information about cards, points to cards_T
 * @param settings - struct which contains information about settings, points to setting_T
*/
void AIAction(Runtime* runtime, Player player[], Cards cards[], Settings* settings)
{
    printf((settings->colors == 1) ? ai_action_color : ai_action);

    bool can_do_4 = false;
    int temp_player;
    int id, number, color;
    int current_player_turn = runtime->player_turn;

    int length = sizeof(player[runtime->player_turn].cards) / sizeof(player[runtime->player_turn].cards[0]);
    bool isPresent;

    do
    { 
        number = (rand() % ((settings->swap_card == 1) ? 15 : 14 - 0 + 0) + 0);
        color = (rand() % (4 - 1 + 1) + 1);

        for (int i = 0; i < length; i++) 
        {
            if ((player[runtime->player_turn].cards[i].number == number) | (player[runtime->player_turn].cards[i].color == color)) 
            {
                isPresent = true;
                id = i;
                break;
            }
        }
    } while (!isPresent);

    if ((number == 0) | (number < 10))
    {
        player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
        player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
        player->number_of_cards--;
    }

    else
    {
        int next = NextPlayer(runtime, settings, true);
        int num_cards = player[1].number_of_cards;
        switch (number) 
        {
            case 10:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player[runtime->player_turn].number_of_cards--;

                for (int i = 1; i < 3; i++)
                {
                    player[next].cards[num_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];

                    runtime->avabible_cards--;
                    player[next].number_of_cards++;

                    if (settings->debug_mode)
                    {
                        VectorPushBack(&player[runtime->player_turn].test, (void*)50);
                        printf("[DEBUG [TEST] ] Element test: %d\n", (int)VectorGet(&player[runtime->player_turn].test, 0));
                    }
                }

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

                return;
                break;

            case 11:
                if (runtime->isPositive == true)
                    runtime->isPositive = false;
                else
                    runtime->isPositive = true;

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);

                return;
                break;

            case 12:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");
		
                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

                return;
                break;

            case 13:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player[runtime->player_turn].number_of_cards--;

                runtime->top_card[0].number = 0;
                runtime->top_card[0].color = (rand() % (4 - 1 + 1)) + 1;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);

                return;
                break;

            case 14:
                for (int i = 0; i < player->number_of_cards + 1; i++)
                {
                    if (player[runtime->player_turn].cards[i].color != runtime->top_card[0].color)
                    {
                        player[runtime->player_turn].legal_four = true;
                    }

                    else
                    {
                        player[runtime->player_turn].legal_four = false;
                    }
                }

                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                for (int i = 1; i < 5; i++)
                {
                    player[next].cards[num_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];

                    runtime->avabible_cards--;
                    player[next].number_of_cards++;

                    if (settings->debug_mode)
                    {
                        VectorPushBack(&player[runtime->player_turn].test, (void*)50);
                        printf("[DEBUG [TEST] ] Element test: %d\n", (int)VectorGet(&player[runtime->player_turn].test, 0));
                    }
                }

                runtime->top_card[0].number = 0;
                runtime->top_card[0].color = (rand() % (4 - 1 + 1)) + 1;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);
                NextPlayer(runtime, settings, false);

            return;
            break;

            case 15:
                player[runtime->player_turn].cards[runtime->current_card_id].number = 0;
                player[runtime->player_turn].cards[runtime->current_card_id].color = 0;
                player->number_of_cards--;

                temp_player = (rand() % (settings->players - 1 + 1) + 1);
                Swap(runtime, player, temp_player);
                printf("AI Player %d swapped with Player %d\n", runtime->player_turn, temp_player);

                for (int i = 1; i < player[runtime->player_turn].number_of_cards + 1; i++)
                {
                    printf((settings->colors == 1) ? card_info_color : card_info, i, player[runtime->player_turn].cards[i].number, 
                                                                                    player[runtime->player_turn].cards[i].color);
                }

                runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
                runtime->avabible_cards--;

                printf("\t -------------------- \t \n");
                printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
                printf("\t -------------------- \t \n");

                NextPlayer(runtime, settings, false);
                return;
                break;

            default:
                return;
                break;
        }
    }

    player[runtime->player_turn].cards[id].number = 0;
    player[runtime->player_turn].cards[id].color = 0;
    player[runtime->player_turn].number_of_cards--;

    runtime->player_turn = current_player_turn;
    for (int i = 1; i < player[runtime->player_turn].number_of_cards + 1; i++)
    {
        printf((settings->colors == 1) ? card_info_color : card_info, i, player[runtime->player_turn].cards[i].number, 
                                                            player[runtime->player_turn].cards[i].color);
    }

    runtime->top_card[0].number = 0;
    runtime->top_card[0].color = 0;
    runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];
    runtime->avabible_cards--;

    printf("\t -------------------- \t \n");
    printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
    printf("\t -------------------- \t \n");

    NextPlayer(runtime, settings, false);
}

/**
 * Read or write points to text file.
 * @param points - struct for holding information about points, points to points_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param write - perform read of write
 * @param players - number of players
 * @param point - points, see function code in gameplay.c for naming convention
*/
int PointsFromFile(Points* points, Settings* settings, bool write, int player, int point)
{
    points->alReadyCreated = false;
    if (!write)
    {
        FILE* read = fopen(points->points_path, "r");
        char buffer[14];
        char points_buffer[4]; /* To remove "Player 0: " text */
        char player_buffer[3]; /* For player id */

        if (read == NULL && !points->alReadyCreated)
        {
            /*
             * If the file doesn't exist, create it and set players' points to 0.
            */

            FILE* temp = fopen(points->points_path, "w");
            fclose(temp);
            points->alReadyCreated = true;
            PointsFromFile(points, settings, true, 0, 0);
            PointsFromFile(points, settings, write, player, point);
        }

        else if (read == NULL && points->alReadyCreated)
        {
            printf("Error reading points from file!\n");
            return 1;
        }

        while (fgets(buffer, sizeof(buffer), read))
        {
            if (strlen(buffer) == 1)
            {
                
            }

            else
            {
                if (buffer[12] == '\n')
                {
                    buffer[12] = '\0';
                }

                /* copy points to points_buffer */
                strncpy(points_buffer, buffer + 10, 3);
                points_buffer[3] = '\0';

                /* copy player id to player_buffer */
                strncpy(player_buffer, buffer + 7, 2);
                player_buffer[2] = '\0';

                if (player_buffer[1] == ':')
                {
                    player_buffer[1] = '\0';
                }

                if (atoi(player_buffer) == player)
                {
                    points->temp_points += atoi(points_buffer);
                }
            }
        }

        fclose(read);
        return 0;
    }

    else
    {
        /*
        * Naming convention for `point` variabel:
        * 0 = write defaults
        * 1 = ignore
        * other = write a point
        */

        if (point == 0)
        {
            FILE* write = fopen(points->points_path, "w");
            if (write == NULL)
            {
                printf("\t Error: Could not open file\n");
                return 0;
            }

            for (int i = 0; i < settings->players; i++)
            {
                fprintf(write, "Player %d: 0\n", i);
            }

            fclose(write);
        }

        else if (point != 1)
        {
            char new_text[14];
            sprintf(new_text, "Player %d: %d", player, point);
            replace_line(points->points_path, player + 1, 14, new_text);
        }

        else
        {
            /* ignoring 1 */
        }
    }

    return 0;
}

/**
 * Assigning points and determining winner of the match.
 * @param player - struct which contains information about player, points to player_T
 * @param settings - struct which contains information about settings, points to setting_T
 * @param points - struct for holding information about points, points to points_T
 * @param players - number of players
*/
void PointsManager(Player player[], Settings* settings, Points* points, int players)
{
    int temp_points = 0;

    for (int i = 0; i < players - 1; i++)
    {
        for (int j = 1; j < player[i].number_of_cards + 1; j++)
        {
            if (player[i].cards[j].number < 10 || player[i].cards[j].number == 15)
            {
                temp_points += player[i].cards[j].number;
            }

            else
            {
                if (player[i].cards[j].number >= 10 && player[i].cards[j].number <= 12)
                {
                    temp_points += 20;
                }

                else if (player[i].cards[j].number >= 13 && player[i].cards[j].number < 15)
                {
                    temp_points += 40;
                }
            }
        }
    }
    points->temp_points = temp_points;
    PointsFromFile(points, settings, false, points->round_winner, 0); /* Read points from file */
    PointsFromFile(points, settings, true, points->round_winner, points->temp_points); /* Write points to file */
    if (PointsFromFile(points, settings, false, points->round_winner, 0) == 1)
    {
        printf("Error reading points from file!\n");
        printf("Continuing without them!\n");
        return;
    }

    if (points->temp_points >= points->match_points)
    {
        points->match_ended = true;
        points->match_winner = points->round_winner;
        remove(points->points_path);
        return;
    }
}

/**
 * Entry point for gameplay mechanics, calls all other functions in gameplay.h and gameplay.c.
 * @param settings - struct which contains information about settings, points to setting_T
 * @param points - struct for holding information about points, points to points_T 
 * @param theme - struct for holding graphics (theme releated stuff mostly) informations during runtime, points to theme_t
*/
void Gameplay(Settings* settings, Points* points, Theme* theme)
{
    char tmp_input[20];
    time_t t;

    int players = settings->players;

    Cards cards[109];
    Player player[players];
    Runtime* runtime = malloc(sizeof(Runtime));

    runtime->current_card_id = 0;
    runtime->player_turn = 0;
    runtime->isPositive = true;

    srand((unsigned) time(&t));
    GenerateDeck(runtime, cards, settings);
    
    /* Print all cards */
    if (settings->debug_mode == 1)
    {
        printf("Cards: \n");

        for (int i = 0; i < runtime->avabible_cards; i++)
        {
            printf((settings->colors == 1) ? all_cards_color : all_cards, cards[i].number, cards[i].color);
        }
    }

    /* Deal the cards to players */
    for (int i = 0; i < players; i++)
    {
        player[i].number_of_cards = 0;
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

        player[i].legal_four = false;
        VectorInit(&player[i].test);
    }

    runtime->top_card[0] = cards[rand() % (runtime->avabible_cards - 5 + 5) + 5]; /* we cannot get wild draw four card */
    runtime->avabible_cards--;

    player[0].cards[2].number = 10;
    player[0].cards[2].color = runtime->top_card[0].color;

    printf("\t -------------------- \t \n");
    printf((settings->colors == 1) ? top_card_color : top_card, runtime->top_card[0].number, runtime->top_card[0].color);
    printf("\t -------------------- \t \n");

    TopCardAction(runtime, player, cards, settings);

    if (settings->debug_mode == 1)
    {
        printf("[DEBUG] Avabible cards: %d\n", runtime->avabible_cards);
    }

    while (true)
    {
        if (isFinished(player, points, settings) == true)
        {
            PointsManager(player, settings, points, players);
            printf((settings->colors == 1) ? game_finished_color : game_finished);

            if (points->match_ended)
            {
                printf((settings->colors == 1) ? won_match_color : won_match, points->match_winner);
                printf((settings->colors == 1) ? points_color : points_text, points->match_points);
                break;
            }

            else
            {
                printf((settings->colors == 1) ? won_round_color : won_round, points->round_winner);
                printf((settings->colors == 1) ? points_color : points_text, points->temp_points);
                printf("------------------\n");
            }
        }

        again:
        if (runtime->player_turn != 0 && (char)VectorGet(&settings->ai_sequence, runtime->player_turn) == '1')
        {
            AIAction(runtime, player, cards, settings);
            goto again;
        }

        else if (runtime->player_turn != 0 && (char)VectorGet(&settings->network_sequence, runtime->player_turn) == '1')
        {
            printf("Network is WIP (Work in progress)!!\n\n");
            NextPlayer(runtime, settings, false);
            goto again;
        }

        else
        {
            printf((settings->colors == 1) ? player_turn_color : player_turn, runtime->player_turn);
        }
        try_again:
        printf((settings->colors == 1) ? option_color : option_text);
        scanf("%s", tmp_input);

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
				printf((settings->colors == 1) ? card_info_color : card_info, i, player[runtime->player_turn].cards[i].number, 
                                                                    player[runtime->player_turn].cards[i].color);
			}
			goto try_again;
		}

        else if (strcmp(tmp_input, "doubt") == 0)
        {
            int current_turn = runtime->player_turn;
            runtime->isPositive = false;
            if (runtime->top_card[0].number == 14 && runtime->top_card[0].color == 0 && player[NextPlayer(runtime, settings, true)].legal_four == false)
            {
                printf("Player illegally played wild draw four card!\n");
            }

            else
            {
                printf("Player legally played wild draw four card!\n");

                player[runtime->player_turn].cards[player[runtime->player_turn].number_of_cards].number = 0;
                player[runtime->player_turn].cards[player[runtime->player_turn].number_of_cards].color = 0;

                for (int i = 1; i < 3; i++)
                {
                    player[current_turn].cards[player[current_turn].number_of_cards + i] = cards[rand() % (runtime->avabible_cards - 1 + 1) + 1];

                    runtime->avabible_cards--;
                    player->number_of_cards++;
                }
            }
        }

        else if (strcmp(tmp_input, "theme") == 0 && settings->debug_mode == 1) /* here because of those flags for strict code */
        {
            printf("%d\n", theme->dark);
            goto try_again;
        }

        else if (strcmp(tmp_input, "exit") == 0)
        {
            printf((settings->colors == 1) ? exiting_color : exiting);
            break;
        }

        else
        {
            runtime->current_card_id = atoi(tmp_input);
        }

        if (isCompatible(runtime, player))
        {
            /* take new top card and go to other player */
            Action(runtime, player, cards, settings);

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
    
    /* Frees structs */
    free(runtime);
}
