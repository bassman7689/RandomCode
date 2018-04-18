#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>
#include "env.h"
#include "eval.h"
#include "ast.h"
#include "reader.h"
#include "printer.h"

void rep(char *code, Env *env) {
	mal_val *ast;
	ast = READ(code);
	ast = EVAL(ast, env);
	if(ast == NULL)
	{
		return;
	}
	PRINT(ast);
	mal_val_free(ast);
}

int main(int argc, char **argv) {
	Env *env = build_default_env();

	while(1) {
		/* Output our prompt and get input */
		char * input = readline("user> ");
		if (!input) { break; }

		/* Add input to history */
		add_history(input);

		rep(input, env);

		free(input);
	}
	env_destroy(env);
	return 0;
}
