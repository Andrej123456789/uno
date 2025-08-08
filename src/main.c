/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++
 * LICENSE: MIT License
 * DESCRIPTION: Entry point of the program
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <json-c/json.h>

#include "include/gameplay.h"

char logo[11][106] =
{
    ".----------------.  .-----------------. .----------------.  .----------------.  .----------------.  ",
    "| .--------------. || .--------------. || .--------------. || .--------------. || .--------------. |",
    "| | _____  _____ | || | ____  _____  | || |     ____     | || |      _       | || |      _       | |",
    "| ||_   _||_   _|| || ||_   \\|_   _| | || |   .'    `.   | || |     | |      | || |     | |      | |",
    "| |  | |    | |  | || |  |   \\ | |   | || |  /  .--.  \\  | || |  ___| |___   | || |  ___| |___   | |",
    "| |  | '    ' |  | || |  | |\\ \\| |   | || |  | |    | |  | || | |___   ___|  | || | |___   ___|  | |",
    "| |   \\ `--' /   | || | _| |_\\   |_  | || |  \\  `--'  /  | || |     | |      | || |     | |      | |",
    "| |    `.__.'    | || ||_____|\\____| | || |   `.____.'   | || |     |_|      | || |     |_|      | |",
    "| |              | || |              | || |              | || |              | || |              | |",
    "| '--------------' || '--------------' || '--------------' || '--------------' || '--------------' |",
    " '----------------'  '----------------'  '----------------'  '----------------'  '----------------'"
};

/**
 * Copy settings from JSON to the structs.
 * @param runtime struct containing runtime information 
 * @param tweaks struct containing tweaks settings
 * @param points struct containing information related to points storing
 * @param path path of the JSON file
*/
int copy_json(Runtime* runtime, Tweaks* tweaks, Points* points, char* path)
{
    struct json_object_iterator it;
    struct json_object_iterator itEnd;

    json_object* root = json_object_from_file(path);
    if (root == NULL)
    {
        return 1;
    }

    it = json_object_iter_init_default();
    it = json_object_iter_begin(root);
    itEnd = json_object_iter_end(root);

    while (!json_object_iter_equal(&it, &itEnd))
    {
        const char* key = json_object_iter_peek_name(&it);
        json_object* val = json_object_iter_peek_value(&it);

        if (strcmp(key, "match_points") == 0)
        {
            points->match_points = json_object_get_int(val);

            if (points->match_points < 1 || points->match_points == INT32_MAX)
            {
                printf("Invalid number of match points!\n");
                printf("Allowed range: [1, INT32_MAX>\n");

                return 1;
            }
        }

        else if (strcmp(key, "points_path") == 0)
        {
            strncpy(points->path, json_object_get_string(val), 255);
            points->path[256] = '\0';
        }

        else if (strcmp(key, "players") == 0)
        {
            runtime->number_of_players = json_object_get_int(val);

            if (runtime->number_of_players < 2 || runtime->number_of_players == INT32_MAX)
            {
                printf("Invalid number of players!\n");
                printf("Allowed range [2, INT32_MAX>\n");

                return 1;
            }
        }

        else if (strcmp(key, "tweaks") == 0)
        {
            struct json_object* tweaks_json;
            
            struct json_object_iterator it2;
            struct json_object_iterator itEnd2;

            for (size_t i = 0; i < json_object_array_length(val); i++)
            {
                struct json_object* element = json_object_array_get_idx(val, i);
                tweaks_json = json_tokener_parse(json_object_get_string(element));
            }

            it2 = json_object_iter_init_default();
            it2 = json_object_iter_begin(tweaks_json);
            itEnd2 = json_object_iter_end(tweaks_json);

            while (!json_object_iter_equal(&it2, &itEnd2))
            {
                const char* key2 = json_object_iter_peek_name(&it2);
                json_object* val2 = json_object_iter_peek_value(&it2);

                if (strcmp(key2, "colors") == 0)
                {
                    tweaks->colors = json_object_get_boolean(val2);
                }

                else if (strcmp(key2, "stacking") == 0)
                {
                    tweaks->stacking = json_object_get_boolean(val2);
                }

                else if (strcmp(key2, "swap_card") == 0)
                {
                    tweaks->swap_card = json_object_get_boolean(val2);
                }

                else if (strcmp(key2, "seven_o") == 0)
                {
                    tweaks->seven_o = json_object_get_boolean(val2);
                }

                json_object_iter_next(&it2);
            }

            json_object_put(tweaks_json);
        }

        json_object_iter_next(&it);
    }

    json_object_put(root);
    return 0;
}

/**
 * Entry point.
 */
int main(int argc, const char** argv)
{
    for (int i = 0; i < 11; i++)
    {
        printf("%s\n", logo[i]);
    }

    char settings_path[257];
    if (argc == 2)
    {
        strncpy(settings_path, argv[1], 255);
        settings_path[256] = '\0';
    }

    else
    {
        printf("Usage: ./main <path to the settings file>\n");
        printf("Example: ./main settings/default.json\n");
        printf("\n");

        printf("Enter the path to the file: ");
        scanf("%255s", settings_path);
    }

    Points points =
    {
        .path = {'\0'},
        .match_points = 0,
    };

    Runtime* runtime = malloc(sizeof(Runtime));
    if (runtime == NULL)
    {
        printf("Error during memory allocation!\nExiting...\n");
        return 0;
    }

    Tweaks* tweaks = malloc(sizeof(Tweaks));
    if (tweaks == NULL)
    {
        printf("Error during memory allocation!\nExiting...\n");

        free(runtime);
        return 0;
    }

    runtime->current_player = 0;
    runtime->isPositive = true;

    runtime->stacking.happening = false;
    runtime->stacking.type = 0;
    runtime->stacking.number_of_cards = 0;

    int result = copy_json(runtime, tweaks, &points, settings_path);
    if (result == 0)
    {
        Gameplay(runtime, tweaks, &points);
    }

    /* Frees structs */
    free(runtime);
    free(tweaks);

    return 0;
}
