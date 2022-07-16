#include "include/util.h"

int copy(struct setting_t* settings, char path[20])
{
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
            
            default:
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
    printf("\n");

    return 0;
}