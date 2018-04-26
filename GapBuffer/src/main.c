#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Gap Buffer

typedef struct gap_buffer_t {
    char* buffer;
    unsigned int gap_start;
    unsigned int gap_end;
    unsigned int size;
} gap_buffer;

gap_buffer* new_gap_buffer(unsigned int size) {
    gap_buffer* gb = malloc(sizeof(gap_buffer));
    gb->buffer = malloc(sizeof(char) * size);
    gb->gap_start = 0;
    gb->gap_end = size;
    gb->size = size;
    return gb;
}

void gap_buffer_grow(gap_buffer *gb) {
    unsigned int new_size = gb->size * 2;

    char * new_buffer = malloc(sizeof(char) * new_size);
    memmove(new_buffer, gb->buffer, gb->gap_start);

    unsigned int new_gap_end = new_size - (gb->size - gb->gap_end);
    memmove(new_buffer + new_gap_end, gb->buffer + gb->gap_end, gb->size - gb->gap_end);

    free(gb->buffer);

    gb->buffer = new_buffer;
    gb->gap_end = new_gap_end;
    gb->size = gb->size * 2;
}

void gap_buffer_move_gap(gap_buffer *gb, unsigned int position) {
    if (position < gb->gap_start) {
        unsigned int gap_delta = gb->gap_start - position;

        gb->gap_start -= gap_delta;
        gb->gap_end -= gap_delta;

        memmove(gb->buffer + gb->gap_end, gb->buffer + gb->gap_start, gap_delta);
    } else if (position > gb->gap_start) {
        unsigned int gap_delta = position - gb->gap_start;

        memmove(gb->buffer + gb->gap_start, gb->buffer + gb->gap_end, gap_delta);

        gb->gap_start += gap_delta;
        gb->gap_end += gap_delta;
    }
}

void gap_buffer_insert_character_at_position(gap_buffer* gb, char character, unsigned int position) {
    gap_buffer_move_gap(gb, position);

    gb->buffer[gb->gap_start] = character;
    gb->gap_start++;

    if (gb->gap_start == gb->gap_end) {
        gap_buffer_grow(gb);
    }
}

void gap_buffer_delete_back(gap_buffer* gb, unsigned int position) {
    gap_buffer_move_gap(gb, position);
    gb->gap_start--;
}

void gap_buffer_delete_forward(gap_buffer* gb, unsigned int position) {
    gap_buffer_move_gap(gb, position);
    gb->gap_end++;
}


void gap_buffer_debug_print(gap_buffer *gb) {
    unsigned int i;

    for(i = 0; i < gb->gap_start; i++) {
        printf("%c", gb->buffer[i]);
    }

    for (i = gb->gap_start; i < gb->gap_end; i++) {
        printf("-");
    }

    for (i = gb->gap_end; i < gb->size; i++) {
        printf("%c", gb->buffer[i]);
    }

    printf("\n");
}

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
    int size = format_string_size("%s", message); 
    char *test_string = malloc(sizeof(char) * size + 1);
    strncat(test_string, message, size);
    to_upper_string(test_string);
    printf("Test: %s\n", test_string);
    free(test_string);
}
