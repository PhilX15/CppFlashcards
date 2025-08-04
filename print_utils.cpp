#include "print_utils.h"

void clear_scr() {
    system("clear");
}

void print_frame(const char *text) {
    char *text_copy = strdup(text);
    if (text_copy == NULL) {
        return;
    }
    format_text(text_copy, LINE_LENGTH);
    unsigned int width = get_max_line_length(text_copy) + 2 * OFFSET_X + 2;
    unsigned int height = get_lines(text_copy) + 2 * OFFSET_Y + 2;
    char **lines = tokenize(text_copy, height - 2 * OFFSET_Y - 2);

    free(text_copy);

    size_t current_line = 0;
    for (size_t i = 0; i < height; i++) {
        for (size_t j = 0; j < width; j++) {
            if ((i == 0 && j == 0) || (i == height - 1 && j == 0) || (i == 0 && j == width - 1) || (i == height - 1 && j == width - 1)) {
                printf("+");
            } else if (i == 0 || i == height - 1) {
                printf("-");
            } else if (j == 0 || j == width - 1) {
                printf("|");
            } else if (i <= OFFSET_Y || i >= height - OFFSET_Y - 1 || j <= OFFSET_X || j >= strlen(*(lines + current_line)) + OFFSET_X + 1) {
                printf(" ");
            } else {
                printf("%c", *(*(lines + current_line) + j - OFFSET_X - 1));
            }
        }
        if (i > OFFSET_Y && i < height - OFFSET_Y - 1) {
            current_line++;
        }
        printf("\n");
    }

    for (size_t i = 0; i < height - 2 * OFFSET_Y - 2; i++) {
        free(*(lines + i));
    }
    free(lines);
}

void format_text(char *text, size_t max_line_length) {
    size_t line_length = 0;
    for (size_t i = 0; i < strlen(text); i++) {
        if (*(text + i) == ' ' && line_length > max_line_length) {
            *(text + i) = '\n';
            line_length = 0;
        } else if (*(text + i) == '\n') {
            line_length = 0;
        } else {
            line_length++;
        }
    }
}

char **tokenize(char *text, size_t count) {
    int ends_with_new_line = (*(text + strlen(text) - 1) == '\n');
    char **lines = (char**) malloc(sizeof(char*) * count);
    if (lines == NULL) {
        return NULL;
    }

    size_t counter = 0;
    char *token = strtok(text, "\n");
    while (token != NULL) {
        *(lines + counter) = strdup(token);
        if (*(lines + counter) == NULL) {
            for (size_t i = 0; i < counter; i++) {
                free(*(lines + i));
            }
            free(lines);
            return NULL;
        }
        token = strtok(NULL, "\n");
        counter++;
    }

    if (ends_with_new_line) {
        *(lines + counter) = strdup("");
    }

    return lines;
}

size_t get_max_line_length(char *text) {
    size_t max = 0;
    size_t line_length = 0;
    for (size_t i = 0; i < strlen(text); i++) {
        if (*(text + i) == '\n') {
            if (line_length > max) {
                max = line_length;
            }
            line_length = 0;
        } else {
            line_length++;
        }
    }

    if (line_length > max) {
        max = line_length;
    }

    return max;
}

size_t get_lines(char *text) {
    size_t count = 1;
    for (size_t i = 0; i < strlen(text); i++) {
        if (*(text + i) == '\n') {
            count++;
        }
    }

    return count;
}