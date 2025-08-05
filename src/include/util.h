/**
 * @author Andrej123456789 (Andrej Bartulin)
 * PROJECT: uno++, simple game inspired by Uno in terminal
 * LICENSE: MIT License
 * DESCRIPTION: util.h, header file for helper functions
*/

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <json-c/json.h>

#include "runtime.h"
#include "c_vector.h"

/**
 * Copying settings from JSON file to the struct
 * @param settings - struct where to copy most of settings 
 * @param points - struct where is `match_point` variable going
 * @param network - struct which holds all informations about network
 * @param path - path of the file, length is 40
*/
int copy_json(Settings* settings, Points* points, Network* network, char* path);

/**
 * Replacing line in the file.
 * Credits: https://codeforwin.org/2018/02/c-program-replace-specific-line-a-text-file.html
 * @param path - the path to the file
 * @param line - the line number
 * @param text_size - size of new text
 * @param text - the new text
*/
void replace_line(const char* path, int line, int text_size, char new_text[text_size]);
