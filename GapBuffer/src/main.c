#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "gap_buffer.h"

// character functions

char to_lower(char character)  {
    if (character >= 'A' && character <= 'Z') {
        return character + ('a' - 'A');
    } else {
        return character;
    }
}

char to_upper(char character)  {
    if (character >= 'a' && character <= 'z') {
        return character - ('a' - 'A');
    } else {
        return character;
    }
}

// string functions

char *to_upper_n(char *str, int n) {
    for (int i = 0; i < n; i++) {
        str[i] = to_upper(str[i]);
    }
    return str;
}

void to_upper_string(char *str) {
    to_upper_n(str, strlen(str));
}

void capatilize_string(char *str) {
    str[0] = to_upper(str[0]);
}

int format_string_size(char *format, ...) {
    int size = 0;
    va_list args;

    va_start(args, format);

    size = vsnprintf(NULL, 0, format, args);

    va_end(args);

    return size;
}

char *message  = "hello, world!";

int main(int argc, char** argv) {
    gap_buffer *buffer = new_gap_buffer(2);
    for (char c = 'A'; c <= 'Z'; c++) {
        gap_buffer_insert_character_at_position(buffer, c, 0);
        gap_buffer_insert_character_at_position(buffer, to_lower(c), 1);
        gap_buffer_debug_print(buffer);
    }

    int size = format_string_size("%s", message); 
    char *test_string = malloc(sizeof(char) * size + 1);
    strncat(test_string, message, size);
    to_upper_string(test_string);
    printf("Test: %s\n", test_string);
    free(test_string);
    free_gap_buffer(buffer);
}
