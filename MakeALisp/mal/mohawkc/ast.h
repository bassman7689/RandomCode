#ifndef AST_H
#define AST_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <glib.h>

typedef enum mal_types {
	MAL_SYMBOL,
	MAL_NUMBER,
	MAL_LIST,
	MAL_OP,
	MAL_ERROR,
	MAL_NIL,
	MAL_TRUE,
	MAL_FALSE
} mal_types;

typedef int (*op_func)(GArray*);

typedef struct mal_val {
	mal_types type;
	union {
		long int num;
		char *symbol;
		GArray *children;
		op_func func;
		char *message;
	} val;

} mal_val;

mal_val *mal_val_new(mal_types type); 
mal_val *mal_val_dup(mal_val *mval);
void mal_val_free(mal_val *mval);

mal_val *mal_val_new_integer(long int val);
mal_val *mal_val_new_list();
mal_val *mal_val_new_symbol(char *symbol);
mal_val *mal_val_new_op(op_func op);
mal_val *mal_val_new_error(char *message);
mal_val *mal_val_new_nil();
mal_val *mal_val_new_true();
mal_val *mal_val_new_false();

#endif
