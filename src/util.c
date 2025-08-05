/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: MIT License
 * DESCRIPTION: util.c, C file for helper functions
*/

#include "include/util.h"

/**
 * Copying settings from JSON file to the struct
 * @param settings - struct where to copy most of settings 
 * @param points - struct where is `match_point` variable going
 * @param network - struct which holds all informations about network
 * @param path - path of the file, length is 40
*/
int copy_json(Settings* settings, Points* points, Network* network, char* path)
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object *root = json_object_from_file(path);
    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    char* temp_sequence = malloc(sizeof(char));

    settings->ai_sequence = NULL;
    settings->network_sequence = NULL;

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);
        /* printf("%s  -> '%s'\n", key, json_object_get_string(val)); */    

        if (strcmp(key, "match_points") == 0)
        {
            points->match_points = atoi(json_object_get_string(val));
        }

        else if (strcmp(key, "points_path") == 0)
        {
            strcpy(points->points_path, json_object_get_string(val));
        }

        else if (strcmp(key, "debug_mode") == 0)
        {
            settings->debug_mode = atoi(json_object_get_string(val));
        }

        else if (strcmp(key, "colors") == 0)
        {
            settings->colors = atoi(json_object_get_string(val));
        }

        else if (strcmp(key, "players") == 0)
        {
            settings->players = atoi(json_object_get_string(val));
        }

        else if (strcmp(key, "special") == 0)
        {
            char* buffer = malloc(sizeof(char) * 1024);
            strcpy(buffer, json_object_get_string(val));

            if (buffer[0] == '[')
            {
                memmove(buffer, buffer + 1, strlen(buffer));
            }
            buffer[strlen(buffer)-1] = '\0';

            struct json_object* parsed_special;
            struct json_object* j_swap_card;
            struct json_object* j_stacking; 
            struct json_object* j_seven_o;

            int swap_card, stacking, seven_o;
            parsed_special = json_tokener_parse(buffer);

            json_object_object_get_ex(parsed_special, "swap_card", &j_swap_card);
            json_object_object_get_ex(parsed_special, "stacking", &j_stacking);
            json_object_object_get_ex(parsed_special, "seven_o", &j_seven_o);

            swap_card = json_object_get_int(j_swap_card);
            stacking = json_object_get_int(j_stacking);
            seven_o = json_object_get_int(j_seven_o);

            /* size of "special elements", swap card, stacking, seven_o */
            settings->special[0] = swap_card;
            settings->special[1] = stacking;
            settings->special[2] = seven_o;

            free(buffer);
        }

        else if (strcmp(key, "ai_sequence") == 0)
        {
            temp_sequence = realloc(temp_sequence, sizeof(char) * json_object_get_string_len(val) + 1);
            strcpy(temp_sequence, json_object_get_string(val));

            for (size_t i = 0; i < strlen(temp_sequence); i++)
            {
                cvector_push_back(settings->ai_sequence, temp_sequence[i]);
            }

            /* Clear the string */
            memset(temp_sequence, 0, strlen(temp_sequence));
        }

        else if (strcmp(key, "network_sequence") == 0)
        {
            temp_sequence = realloc(temp_sequence, sizeof(char) * json_object_get_string_len(val) + 1);
            strcpy(temp_sequence, json_object_get_string(val));

            for (size_t i = 0; i < strlen(temp_sequence); i++)
            {
                cvector_push_back(settings->network_sequence, temp_sequence[i]);
            }

            /* Free the string */
            free(temp_sequence);
        }

        else if (strcmp(key, "network") == 0)
        {
            char* buffer = malloc(sizeof(char) * 1024);
            strcpy(buffer, json_object_get_string(val));

            if (buffer[0] == '[')
            {
                memmove(buffer, buffer + 1, strlen(buffer));
            }
            buffer[strlen(buffer)-1] = '\0';

            struct json_object* parsed_special;
            struct json_object* j_network_sequence;
            struct json_object* j_ip;
            struct json_object* j_port;

            char ip[1024];
            int port;
            parsed_special = json_tokener_parse(buffer);

            json_object_object_get_ex(parsed_special, "network_sequence", &j_network_sequence);
            json_object_object_get_ex(parsed_special, "ip", &j_ip);
            json_object_object_get_ex(parsed_special, "port", &j_port);

            strcpy(ip, json_object_get_string(j_ip));
            port = json_object_get_int(j_port);

            temp_sequence = realloc(temp_sequence, sizeof(char) * json_object_get_string_len(j_network_sequence) + 1);
            strcpy(temp_sequence, json_object_get_string(j_network_sequence));

            for (size_t i = 0; i < strlen(temp_sequence); i++)
            {
                cvector_push_back(settings->network_sequence, temp_sequence[i]);
            }

            /* Free the string */
            free(temp_sequence);

            strcpy(network->ip, ip);
            network->port = port;

            free(buffer);
        }

        else
        {
            if (settings->debug_mode == 1)
            {
                printf("Unknown setting found in JSON file, ignoring it...!");
            }
        }

        json_object_iter_next(&it);
    }
    json_object_put(root);

    /* Print settings */
    printf("Your current settings are (see README.md for details): \n");
    printf("\t Points: \n");
    printf("\t\t Match points: %d\n", points->match_points);
    printf("\t\t Points path: %s\n", points->points_path);

    printf("\t Settings not releated to a gameplay too much: \n");
    printf("\t\t Debug Mode: %d\n", settings->debug_mode);
    printf("\t\t Colors: %d\n", settings->colors);
    printf("\t Gameplay settings: \n");

    printf("\t\t Players: %d\n", settings->players);
    printf("\t\t \"Special\" settings for gameplay: \n");
    printf("\t\t\t Swap card: %d\n", settings->special[0]);
    printf("\t\t\t Stacking: %d\n", settings->special[1]);
    printf("\t\t\t Seven-O: %d\n", settings->special[2]);

    printf("\t Sequences: \n");
    
    /* Print AI sequence */
    printf("\t\t AI sequence: ");
    for (size_t i = 0; i < cvector_size(settings->ai_sequence); ++i)
    {
        printf("%c", settings->ai_sequence[i]);
    }
    printf("\n");

    printf("\t\t \"Network\" settings for gameplay: \n");

    /* Print network sequence */
    printf("\t\t\t Network sequence: ");
    for (size_t i = 0; i < cvector_size(settings->ai_sequence); i++)
    {
        printf("%c", settings->network_sequence[i]);
    }
    printf("\n");

    printf("\t\t\t IP address: %s\n", network->ip);
    printf("\t\t\t Port: %d\n", network->port);

    printf("\n\n");
    return 0;
}

/**
 * Replacing line in the file.
 * Credits: https://codeforwin.org/2018/02/c-program-replace-specific-line-a-text-file.html
 * @param path - the path to the file
 * @param line - the line number
 * @param text_size - size of new text
 * @param text - the new text
*/
void replace_line(const char* path, int line, int text_size, char new_text[text_size])
{
    int count;
    char buffer[1000];

    /* Open all required files */
    FILE* fPtr = fopen(path, "r");
    FILE* fTemp = fopen("replace.tmp", "w");

    /* fopen() return NULL if unable to open file in given mode. */
    if (fPtr == NULL || fTemp == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(0);
    }

    /*
     * Read line from source file and write to destination 
     * file after replacing given line.
    */
    count = 0;
    while ((fgets(buffer, text_size, fPtr)))
    {
        count++;

        /* If current line is line to replace */
        if (count == line)
        {
            fputs(new_text, fTemp);
        }

        else
        {
            fputs(buffer, fTemp);
        }
    }

    /* Close all files to release resource */
    fclose(fPtr);
    fclose(fTemp);

    /* Delete original source file */
    remove(path);

    /* Rename temporary file as original file */
    rename("replace.tmp", path);
}
