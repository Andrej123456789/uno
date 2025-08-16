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

#if defined _WIN32 || defined _WIN64
    #include <Windows.h>
#else
    #include <unistd.h>
#endif

#include <json-c/json.h>

#include "include/gameplay.h"
#include "include/server.h"
#include "include/strings.h"

void Action(Runtime* runtime, Tweaks* tweaks, Network* network, Player* players, cvector_vector_type(Cards)* cards, Cards card)
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
                if (network->enabled == true)
                {
                    send_to_player(&players[runtime->current_player], "\nEnter player's number with whom you want to swap cards: ");
                }

                player = ActionInput(runtime, network, players, runtime->current_player);

                if (player < 0 || player >= runtime->number_of_players)
                {
                    player = !runtime->current_player;
                    printf("Invalid player! Defaulting to %d\n", player);

                    if (network->enabled == true)
                    {
                        send_to_player(&players[runtime->current_player], "Invalid player! Defaulting to %d\n", player);
                    }
                }

                Swap(&players[runtime->current_player], &players[player]);
            }

            break;

        case PLUS_TWO:
            next_player = NextPlayer(runtime, false);

            /* Stacking - move cards */
            if (tweaks->stacking == true && runtime->stacking.happening == true)
            {
                printf((tweaks->colors == true) ? stacking_stacked_color : stacking_stacked);
                if (network->enabled == true)
                {
                    broadcast(players, runtime->number_of_players,
                            (tweaks->colors == true) ? stacking_stacked_color : stacking_stacked);
                }

                for (int i = 0; i < runtime->stacking.number_of_cards; i++)
                {
                    size_t index = cvector_size(players[runtime->current_player].cards);

                    cvector_push_back(players[next_player].cards, players[runtime->current_player].cards[index]);
                    cvector_pop_back(players[runtime->current_player].cards);
                }      
                
                runtime->stacking.number_of_cards += 2;
            }

            /* Usual operation */
            for (int i = 0; i < 2; i++)
            {
                size_t random = GetRandomCard(cards, tweaks);

                cvector_push_back(players[next_player].cards, (*cards)[random]);
                cvector_erase(*cards, random);
            }

            /* Stacking - initialize it */
            if (tweaks->stacking == true && runtime->stacking.happening == false)
            {
                printf((tweaks->colors == true) ? stacking_on_color : stacking_on);
                if (network->enabled == true)
                {
                    broadcast(players, runtime->number_of_players,
                            (tweaks->colors == true) ? stacking_on_color : stacking_on);
                }

                runtime->stacking.happening = true;
                runtime->stacking.type = 2;
                runtime->stacking.number_of_cards = 2;
            }
            
            return;

        case REVERSE_CARD:
            runtime->isPositive = !runtime->isPositive;
            break;

        case SKIP_CARD:
            NextPlayer(runtime, true);
            break;

        case WILD_CARD:
            printf((tweaks->colors == true) ? enter_color_color : enter_color);
            if (network->enabled == true)
            {
                send_to_player(&players[runtime->current_player], (tweaks->colors == true) ? enter_color_color : enter_color);
            }

            color = ActionInput(runtime, network, players, runtime->current_player);

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
            if (network->enabled == true)
            {
                send_to_player(&players[runtime->current_player], (tweaks->colors == true) ? enter_color_color : enter_color);
            }

            color = ActionInput(runtime, network, players, runtime->current_player);

            if (color < 1 || color > 4)
            {
                printf((tweaks->colors == true) ? invalid_color_color : invalid_color);
                color = 1;
            }
            runtime->top_card.color = color;

            /* Doubt */
            printf("Player %d, are you doubting? (0 - no, 1 - yes): ", player_to_draw);
            if (network->enabled == true)
            {
                send_to_player(&players[player_to_draw], "Player %d, are you doubting? (0 - no, 1 - yes): ", player_to_draw);
            }

            doubt = ActionInput(runtime, network, players, player_to_draw);

            if (doubt != 1)
            {
                printf("Not doubting!\n");
                if (network->enabled == true)
                {
                    send_to_player(&players[player_to_draw], "Not doubting!\n");
                }
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
                    printf((tweaks->colors == true) ? doubt_correct_color : doubt_correct);

                    if (network->enabled == true)
                    {
                        broadcast(players, runtime->number_of_players,
                                  (tweaks->colors == true) ? doubt_correct_color : doubt_correct);
                    }

                    player_to_draw = runtime->current_player;
                }

                else
                {
                    printf((tweaks->colors == true) ? doubt_incorrect_color : doubt_incorrect);

                    if (network->enabled == true)
                    {
                        broadcast(players, runtime->number_of_players,
                                  (tweaks->colors == true) ? doubt_incorrect_color : doubt_incorrect);
                    }

                    number_of_cards_to_draw = 6;
                }
            }

            /* Stacking - move cards */
            if (tweaks->stacking == true && runtime->stacking.happening == true)
            {
                printf((tweaks->colors == true) ? stacking_stacked_color : stacking_stacked);
                if (network->enabled == true)
                {
                    broadcast(players, runtime->number_of_players,
                            (tweaks->colors == true) ? stacking_stacked_color : stacking_stacked);
                }

                for (int i = 0; i < runtime->stacking.number_of_cards; i++)
                {
                    size_t index = cvector_size(players[runtime->current_player].cards);

                    cvector_push_back(players[next_player].cards, players[runtime->current_player].cards[index]);
                    cvector_pop_back(players[runtime->current_player].cards);
                }

                runtime->stacking.number_of_cards += 4;
            }

            /* Draw cards */
            for (int i = 0; i < number_of_cards_to_draw; i++)
            {
                size_t random = GetRandomCard(cards, tweaks);

                cvector_push_back(players[player_to_draw].cards, (*cards)[random]);
                cvector_erase(*cards, random);
            }

            /* Stacking - initialize it */
            if (tweaks->stacking == true && runtime->stacking.happening == false)
            {
                printf((tweaks->colors == true) ? stacking_on_color : stacking_on);
                if (network->enabled == true)
                {
                    broadcast(players, runtime->number_of_players,
                            (tweaks->colors == true) ? stacking_on_color : stacking_on);
                }

                runtime->stacking.happening = true;
                runtime->stacking.type = 4;
                runtime->stacking.number_of_cards = 4;
            }

            return;

        case SWAP_CARD:
            printf((tweaks->colors == true) ? enter_color_color : enter_color);
            if (network->enabled == true)
            {
                send_to_player(&players[runtime->current_player], (tweaks->colors == true) ? enter_color_color : enter_color);
            }

            color = ActionInput(runtime, network, players, runtime->current_player);

            if (color < 1 || color > 4)
            {
                printf((tweaks->colors == true) ? invalid_color_color : invalid_color);
                color = 1;
            }
            runtime->top_card.color = color;

            /* ------------------------ */

            printf("\nEnter player's number with whom you want to swap cards: ");
            if (network->enabled == true)
            {
                send_to_player(&players[runtime->current_player], "\nEnter player's number with whom you want to swap cards: ");
            }

            player = ActionInput(runtime, network, players, runtime->current_player);

            if (player < 0 || player >= runtime->number_of_players)
            {
                player = !runtime->current_player;
                printf("Invalid player! Defaulting to %d\n", player);

                if (network->enabled == true)
                {
                    send_to_player(&players[runtime->current_player], "Invalid player! Defaulting to %d\n", player);
                }
            }

            Swap(&players[runtime->current_player], &players[player]);
            break;
        
        default:
            break;
    }

    // +2 and +4 cases exit the function before reaching this point
    // if other card is played, stacking is aborted
    if (tweaks->stacking == true && runtime->stacking.happening == true)
    {
        printf((tweaks->colors == true) ? stacking_off_color : stacking_off);
        if (network->enabled == true)
        {
            broadcast(players, runtime->number_of_players,
                    (tweaks->colors == true) ? stacking_off_color : stacking_off);
        }

        runtime->stacking.happening = false;
        runtime->stacking.type = 0;
        runtime->stacking.number_of_cards = 0;    
    }
}

int ActionInput(Runtime* runtime, Network* network, Player* players, int input_player)
{
    int value = -1;

    if (network->enabled == true)
    {
        char user_input[BUFFER_LIMIT + 1];

        const int TIME_LIMIT_SEC = 30;
        const int POLL_SLEEP_US = 10000; // 10 ms

        time_t deadline = time(NULL) + TIME_LIMIT_SEC;

        /* poll until we get a full line or the timer expires */
        while (!players[input_player].network.ready && time(NULL) < deadline)
        {
            net_poll_clients(players, runtime->number_of_players);   /* non‑blocking socket pump  */

            #if defined _WIN32 || defined _WIN64
                Sleep(POLL_SLEEP_US / 100);    /* nap to save CPU */
            #else
                usleep(POLL_SLEEP_US);         /* nap to save CPU */
            #endif

            value = atoi(user_input);
        }

        if (players[input_player].network.ready)
        {
            strncpy(user_input, players[input_player].network.inbuf, BUFFER_LIMIT - 1);
            user_input[BUFFER_LIMIT] = '\0';

            value = atoi(user_input);
        }

        else
        {
            value = -1;
        }

        /* reset buffer */
        players[input_player].network.inbuf[0] = '\0';
        players[input_player].network.ready = false;
    }

    else
    {
        scanf("%d", &value);
    }

    return value;
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

void PointsManager(Runtime* runtime, Tweaks* tweaks, Points* points, Network* network, Player* players)
{
    printf((tweaks->colors == true) ? game_finished_color : game_finished);
    if (network->enabled == true)
    {
        broadcast(players, runtime->number_of_players,
                  (tweaks->colors == true) ? game_finished_color : game_finished);
    }

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

    printf((tweaks->colors == true) ? won_round_color : won_round,
           runtime->current_player, add_points);

    if (network->enabled == true)
    {
        broadcast(players, runtime->number_of_players,
                  (tweaks->colors == true) ? won_round_color : won_round,
                  runtime->current_player, add_points);
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
            printf((tweaks->colors == true) ? won_match_color : won_match, 
                   runtime->current_player, (current_points + add_points));

            if (network->enabled == true)
            {
                broadcast(players, runtime->number_of_players,
                          (tweaks->colors == true) ? won_match_color : won_match, 
                          runtime->current_player, (current_points + add_points));
            }
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

void Gameplay(Runtime* runtime, Tweaks* tweaks, Points* points, Network* network)
{
    char user_input[BUFFER_LIMIT + 1];
    
    time_t t;
    srand((unsigned) time(&t));
    
    Player* players = calloc(runtime->number_of_players, sizeof(Player));
    cvector_vector_type(Cards) cards = GenerateDeck(tweaks);

    int listener_fd = -1;
    if (network->enabled == true)
    {
        listener_fd = net_start_server(network->port, runtime->number_of_players);
    }

    /* Wait for all clients to join the game */
    if (network->enabled == true)
    {
        uint16_t connected_clients = 0;
        while (connected_clients < runtime->number_of_players)
        {
            connected_clients = 0; // reset counter so it counts all connected clients correctly
            if (listener_fd >= 0) 
            {
                net_accept_clients(listener_fd, players, runtime->number_of_players);
                net_poll_clients(players, runtime->number_of_players);
            }

            for (uint16_t i = 0; i < runtime->number_of_players; i++) 
            {
                if (players[i].network.sockfd > 0) 
                {
                    connected_clients++;
                }
            }
        }
    }

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

                if (network->enabled == true)
                {
                    send_to_player(&players[i],
                                   (tweaks->colors == true) ? player_card_info_color : player_card_info,
                                   i, z, players[i].cards[z].number, players[i].cards[z].color);
                }
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

    Action(runtime, tweaks, network, players, &cards, runtime->top_card);

    bool game_loop = true;
    bool round_ended = false;

    while (game_loop)
    {
        if (listener_fd >= 0) 
        {
            net_accept_clients(listener_fd, players, runtime->number_of_players);
            net_poll_clients(players, runtime->number_of_players);
        }

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

        if (network->enabled == true)
        {
            broadcast(players, runtime->number_of_players, "\t -------------------- \t \n");
            broadcast(players, runtime->number_of_players,
                      (tweaks->colors == true) ? top_card_color : top_card,
                      runtime->top_card.number, runtime->top_card.color);
            broadcast(players, runtime->number_of_players, "\t -------------------- \t \n");
        }

        printf((tweaks->colors == true) ? player_turn_color : player_turn, runtime->current_player);
        if (network->enabled == true)
        {
            broadcast(players, runtime->number_of_players,
                      (tweaks->colors == true) ? player_turn_color : player_turn, runtime->current_player);
        }

        do
        {
            if (network->enabled == true)
            {
                send_to_player(&players[runtime->current_player],
                               (tweaks->colors == true) ? option_color : option_text);

                const int TIME_LIMIT_SEC = 30;
                const int POLL_SLEEP_US = 10000; // 10 ms

                time_t deadline = time(NULL) + TIME_LIMIT_SEC;

                /* poll until we get a full line or the timer expires */
                while (!players[runtime->current_player].network.ready && game_loop && time(NULL) < deadline)
                {
                    net_poll_clients(players, runtime->number_of_players);   /* non‑blocking socket pump  */

                    #if defined _WIN32 || defined _WIN64
                        Sleep(POLL_SLEEP_US / 100);    /* nap to save CPU */
                    #else
                        usleep(POLL_SLEEP_US);         /* nap to save CPU */
                    #endif
                }

                if (players[runtime->current_player].network.ready)
                {
                    strncpy(user_input, players[runtime->current_player].network.inbuf, BUFFER_LIMIT - 1);
                    user_input[BUFFER_LIMIT] = '\0';
                }

                else
                {
                    strcpy(user_input, "<timeout>");
                }

                /* reset buffer */
                players[runtime->current_player].network.inbuf[0] = '\0';
                players[runtime->current_player].network.ready = false;
            }
            
            else
            {
                printf((tweaks->colors == true) ? option_color : option_text);
                scanf("%254s", user_input);
            }

            if (strcmp(user_input, "new") == 0)
            {
                if (alReadyNew == true)
                {
                    printf((tweaks->colors == 1) ? discard_or_play_color : discard_or_play);
                    if (network->enabled == true)
                    {
                        send_to_player(&players[runtime->current_player],
                                       (tweaks->colors == 1) ? discard_or_play_color : discard_or_play);
                    }

                    continue;
                }

                size_t random = GetRandomCard(&cards, tweaks);
                cvector_push_back(players[runtime->current_player].cards, cards[random]);

                printf((tweaks->colors == true) ? new_card_color : new_card,
                       cards[random].number, cards[random].color);

                if (network->enabled == true)
                {
                    send_to_player(&players[runtime->current_player],
                                    (tweaks->colors == true) ? new_card_color : new_card,
                                    cards[random].number, cards[random].color);
                }

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

                        if (network->enabled == true)
                        {
                            send_to_player(&players[runtime->current_player],
                                           (tweaks->colors == true) ? card_info_color : card_info,
                                           i, players[runtime->current_player].cards[i].number,
                                           players[runtime->current_player].cards[i].color);
                        }
                    }
                }
            }

            else if (strcmp(user_input, "discard") == 0)
            {
                NextPlayer(runtime, true);

                if (tweaks->stacking == true && runtime->stacking.happening == true)
                {
                    printf((tweaks->colors == true) ? stacking_off_color : stacking_off);
                    if (network->enabled == true)
                    {
                        broadcast(players, runtime->number_of_players,
                                (tweaks->colors == true) ? stacking_off_color : stacking_off);
                    }

                    runtime->stacking.happening = false;
                    runtime->stacking.type = 0;
                    runtime->stacking.number_of_cards = 0;    
                }

                break;
            }

            else if (strcmp(user_input, "exit") == 0)
            {
                printf((tweaks->colors == true) ? exiting_color : exiting);

                if (network->enabled == true)
                {
                    broadcast(players, runtime->number_of_players,
                              (tweaks->colors == true) ? exiting_color : exiting);
                }

                game_loop = false;
                break;
            }

            else
            {
                card_id = atoi(user_input);
                if (card_id < 0 || (size_t)card_id >= cvector_size(players[runtime->current_player].cards))
                {
                    printf((tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    if (network->enabled == true)
                    {
                        send_to_player(&players[runtime->current_player],
                                       (tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    }

                    continue;
                }

                if (!isCompatible(runtime->top_card, players[runtime->current_player].cards[card_id]))
                {
                    printf((tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    if (network->enabled == true)
                    {
                        send_to_player(&players[runtime->current_player],
                                       (tweaks->colors == true) ? card_not_compatible_color : card_not_compatible);
                    }

                    continue;
                }

                runtime->previous_top_card = runtime->top_card;
                runtime->top_card = players[runtime->current_player].cards[card_id];
                cvector_erase(players[runtime->current_player].cards, card_id);

                Action(runtime, tweaks, network, players, &cards, runtime->top_card);

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
        PointsManager(runtime, tweaks, points, network, players);
    }

    /* Free everything up */
    for (int i = 0; i < runtime->number_of_players; i++)
    {
        cvector_free(players[i].cards);
    }

    free(players);
    cvector_free(cards);
}
