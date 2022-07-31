#include "include/util.h"

int copy(struct setting_t* settings, char path[20])
{
    bool aiDone;

    char line[256];
    int temp = 1;

    FILE* file;
    file = fopen(path, "r");

    if (file == NULL)
    {
        printf("File not found!\n");
        return 1;
    }

    while (fgets(line, sizeof(line), file)) 
    {
        switch (temp)
        {
            case 1: /* number of players */
                if (atoi(line) > 20)
                {
                    printf("Maximum number of players is 20!\n");
                    printf("Exiting...\n\n");
                    return 1;
                }

                settings->players = atoi(line);
                temp++;
                break;

            case 2: /* special_mode */
                settings->special_mode = atoi(line);
                temp++;
                break;

            case 3: /* debug_mode */
                settings->debug_mode = atoi(line);
                temp++;
                break;

            case 4: /* swap_card */
                settings->swap_card = atoi(line);
                temp++;
                break;

            case 5: /* colors */
                settings->colors = atoi(line);
                temp++;
                break;
            
            default: /* ai players */
                if (!aiDone)
                {
                    settings->ai_sequence = atoi(line);
                    aiDone = true;
                }

                else
                {
                    settings->network_sequence = atoi(line);
                }
                break;
        }
    }

    fclose(file);

    printf("Your current settings are:\n");
    printf("\t Players: %d\n", settings->players);
    printf("\t Special Mode: %d\n", settings->special_mode);
    printf("\t Debug Mode: %d\n", settings->debug_mode);
    printf("\t Swap Card: %d\n", settings->swap_card);
    printf("\t Colors: %d\n", settings->colors);
    if (!SetAISequence(settings)) printf("\t Invalid AI sequence!\n");
    if (!SetNetworkSequence(settings)) printf("\t Invalid Network sequence!\n");
    printf("\n");

    return 0;
}