/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: util.h, header file for helper functions
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>

#include "gameplay.h"

/**
 * Copying settings from the file to the struct.
 * @param settings - the struct to copy the settings to
 * @param points - the struct to copy the points (`match_point` variable) to
 * @param path - the path to the file, length must be 20
*/
int copy(struct setting_t* settings, struct points_t* points, char path[20]);

/**
 * Replacing line in the file.
 * Credits: https://codeforwin.org/2018/02/c-program-replace-specific-line-a-text-file.html
 * @param path - the path to the file
 * @param line - the line number
 * @param text_size - size of new text
 * @param text - the new text
*/
void replace_line(const char* path, int line, int text_size, char new_text[text_size]);

/**
 * Dynamically growing array in C
 * Credits: https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
 * @param array . actual array
 * @param used - how much elements are used
 * @param size - size of array
*/
typedef struct 
{
    int *array;
    size_t used;
    size_t size;
} Vec;

/**
 * Initializes an array
 * Credits: https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
 * @param a - array, points to Vec struct
 * @param initSize - size to allocate during initialization
*/
void InitArray(Vec *a, size_t initSize);

/**
 * Insert an element into an array
 * Credits: https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
 * @param a - array, points to Vec struct
 * @param element - element to insert into an array
*/
void InsertArray(Vec *a, int element);

/**
 * Frees an array
 * Credits: https://stackoverflow.com/questions/3536153/c-dynamically-growing-array
 * @param a - array, points to Vec struct
*/
void FreeArray(Vec *a);
