/** \file reader.c 
 * A set of methods that manipulate
 * a reader struct.
 */

#include "reader.h"

GArray *tokenize(char * code)
{
	GError *err = NULL;
	GMatchInfo *matchInfo;
	GRegex *regex;

	regex = g_regex_new(REGEX_PATTERN, 0, 0, &err);

	if(err)
	{
		fprintf(stderr, "Error: problem compiling regex %s\n", err->message);
		exit(1);
	}

	GArray *tokens = g_array_new(FALSE, FALSE, sizeof(char *));

	g_regex_match(regex, code, 0, &matchInfo);

	while(g_match_info_matches(matchInfo))
	{
		gchar *result = g_match_info_fetch(matchInfo, 1);
		if(strcmp(result, "") == 0)
		{
			g_free(result);
			break;
		}

		g_array_append_val(tokens, result);
		g_match_info_next(matchInfo, &err);
		if(err) {
			fprintf(stderr, "Error: problem finding next match %s\n", err->message);
			exit(1);
		}
	}

	return tokens;
}

/**
 * A "constructor" for a reader struct.
 */
Reader *reader_new(GArray *tokens)
{
	Reader *ret;
	ret = malloc(sizeof(Reader));

	if(ret == NULL)
	{
		fprintf(stderr, "Error: Failed to allocate memory for reader.\n");
		exit(1);
	}

	ret->position = 0;
	ret->tokens = tokens;
	return ret;
}

/**
 * A "deconstructor" for the reader struct.
 */
void reader_free(Reader* reader)
{
	if(reader->tokens)
	{
		int i;
		for (i = 0; i < reader->tokens->len; i++)
		{
			g_free(g_array_index(reader->tokens, gchar*, i));
		}
		g_array_free(reader->tokens, FALSE);
	}

	if(reader)
	{
		free(reader);
	}
}

/** 
 * A function to get the current token.
 */
char *reader_peek(Reader *reader)
{
	if(reader->position < reader->tokens->len)
	{
		return g_array_index(reader->tokens, char*, reader->position);
	}

	return  NULL;
}

/**
 * A function to get the current token and 
 * advance to the next token.
 */
char *reader_next(Reader *reader)
{
	if(reader->position < reader->tokens->len)
	{
		char * val = g_array_index(reader->tokens, char*, reader->position);
		reader->position++;
		return val;
	}

	return NULL;
}

mal_val *read_form(Reader *reader)
{
	char * current_token = reader_peek(reader);
	if(current_token == NULL) {
		return mal_val_new_error("Error: Missing ')'.");
	}

	if(current_token[0] == '(')
	{
		return read_list(reader);
	}
	else
	{
		return read_atom(reader);
	}
}

mal_val *read_list(Reader *reader)
{
	GArray *children = g_array_new(FALSE, FALSE, sizeof(mal_val *));
	reader_next(reader);
	char * current_token = reader_peek(reader);

	while(current_token != NULL && *current_token != ')')
	{
		mal_val *current = read_form(reader);
		if(current->type == MAL_ERROR)
		{
			return current;
		}
		g_array_append_val(children, current);
		current_token = reader_peek(reader);
	}

	if (current_token == NULL)
	{
		return mal_val_new_error("Error: Missing ')'.");
	}

	reader_next(reader);
	return mal_val_new_list(children);
}

int try_parse_number(char *s, mal_val **val)
{
	char * cur = s;
	if(s == NULL)
	{
		*val = mal_val_new_error("Error: Missing ')'.");
		return 0;
	}

	while(*cur != '\0')
	{
		if(isdigit(*cur) || (*cur == '-' && *(cur + 1) != '\0'))
		{
			cur++;
		}
		else
		{
			*val = NULL;
			return 0;
		}
	}



	char *end_ptr;
	long int num = strtol(s, &end_ptr, 10);
	// shouldn't be reached but leaving just in case
	if (end_ptr == s) {
		char *error;
		asprintf(&error, "Error: parsing error \"%s\" is not a number.", s);
		*val = mal_val_new_error(error);
		free(error);
		return 0;
	}
	*val = mal_val_new_integer(num);
	return 1;
}

mal_val *read_atom(Reader *reader)
{
	char *current_token = reader_next(reader);
	if(current_token == NULL)
	{
		return mal_val_new_error("Error: Missing ')'.");
	}

	char *s = current_token;

	mal_val *ret;
	int success = try_parse_number(s, &ret);
	if(success || (ret != NULL && ret->type == MAL_ERROR))
	{
		return ret;
	}
	else if(strncmp("true", current_token, strlen("true")) == 0)
	{
		return mal_val_new_true();
	}
	else if(strncmp("false", current_token, strlen("false")) == 0)
	{
		return mal_val_new_false();
	}
	else if(strncmp("nil", current_token, strlen("nil")) == 0)
	{
		return mal_val_new_nil();
	}
	else
	{
		return mal_val_new_symbol(current_token);
	}
}

mal_val *read_str(char *code)
{
	GArray *tokens = tokenize(code);
	Reader *reader = reader_new(tokens);
	mal_val *parsed_ast = read_form(reader);

	reader_free(reader);
	return parsed_ast;
}

mal_val *READ(char *code) {
	return read_str(code);
}

