#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <glib.h>

#include "ast.h"

#define REGEX_PATTERN "[\\s ,]*(~@|[\\[\\]{}()'`~@]|\"(?:[\\\\].|[^\\\\\"])*\"|;.*|[^\\s \\[\\]{}()'\"`~@,;]*)"

typedef struct {
	GArray *tokens;
	int position;
} Reader;

Reader *reader_new(GArray *tokens);
void reader_free(Reader *reader);
GArray *tokenize(char *code);
char *reader_peek(Reader *reader);
char *reader_next(Reader *reader);
mal_val *read_form(Reader *reader);
mal_val *read_list(Reader *reader);
mal_val *read_atom(Reader *reader);
mal_val *read_str(char *code);
mal_val *READ(char *code);

#endif
