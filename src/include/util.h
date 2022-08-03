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
