/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: util.c, c file for helper functions
*/

#include "include/util.h"

/**
 * Copying settings from the file to the struct.
 * @param settings - the struct to copy the settings to
 * @param points - the struct to copy the points (`match_point` variable) to
 * @param path - the path to the file, length must be 20
*/
int copy(struct setting_t* settings, struct points_t* points, char path[20])
{
    bool aiDone;

    char line[256];
    int temp = 0;

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
            case 0: /* match_points */
                points->match_points = atoi(line);
                points->match_ended = false;
                temp++;
                break;

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
    printf("Here: %s\n", new_text);

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
