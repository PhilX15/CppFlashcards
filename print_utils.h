#ifndef PRINT_UTILS_H
#define PRINT_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_LENGTH 20
#define OFFSET_X 3
#define OFFSET_Y 1

void clear_scr();
void print_frame(const char *text);
void format_text(char *text, size_t max_line_length);

char **tokenize(char *text, size_t count);

size_t get_max_line_length(char *text);
size_t get_lines(char *text);

#endif