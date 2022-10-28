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

#include "runtime.h"

/**
 * Copying settings from the file to the struct.
 * @param settings - struct where to copy most of settings
 * @param points - the struct to copy the points (`match_point` variable) to
 * @param path - path of the file, length is 40
*/
int copy(Settings* settings, Points* points, char* path);

/**
 * Copying settings from JSON file to the struct
 * @param settings - struct where to copy most of settings 
 * @param points - struct where is `match_point` variable going
 * @param path - path of the file, length is 40
*/
int copy_json(Settings* settings, Points* points, char* path);

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
