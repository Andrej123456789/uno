/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: Apache License 2.0
 * DESCRIPTION: util.h, header file for helper functions
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <json-c/json.h>

#include "gameplay.h"

/**
 * Copying settings from the file to the struct.
 * @param settings - struct where to copy most of settings
 * @param points - the struct to copy the points (`match_point` variable) to
 * @param path - path of the file, length is 40
*/
int copy(struct setting_t* settings, struct points_t* points, char* path);

/**
 * Copying settings from JSON file to the struct
 * @param settings - struct where to copy most of settings 
 * @param points - struct where is `match_point` variable going
 * @param path - path of the file, length is 40
*/
int copy_json(struct setting_t* settings, struct points_t* points, char* path);

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
 * Check does string ends with another string
 * Credits: https://stackoverflow.com/questions/744766/how-to-compare-ends-of-strings-in-c
 * @param str - base string
 * @param suffix - second string
*/
bool EndsWith(const char* str, const char* suffix);

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
