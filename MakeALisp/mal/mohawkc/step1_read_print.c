#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "ast.h"
#include "reader.h"
#include "printer.h"

mal_val *READ(char *code) {
	return read_str(code);
}

mal_val *EVAL(mal_val *ast) {
	return ast;
}

void PRINT(mal_val *ast) {
	print_str(ast);
}

void rep(char *code) {
	mal_val *ast;
	ast = READ(code);
	ast = EVAL(ast);
	PRINT(ast);
	mal_val_free(ast);
}

int main(int argc, char **argv) {
	while(1) {
		/* Output our prompt and get input */
		char * input = readline("user> ");
		if (!input) { break; }

		/* Add input to history */
		add_history(input);

		rep(input);

		free(input);
	}
	return 0;
}
