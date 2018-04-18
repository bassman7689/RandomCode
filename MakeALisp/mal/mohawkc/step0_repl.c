#include <stdio.h>
#include <stdlib.h>

#include <editline/readline.h>

char *READ(char *read) {
	return read;
}

char *EVAL(char *eval) {
	return eval;
}

char *PRINT(char *print) {
	return print;
}

char *rep(char *code) {
	char *ret;
	ret = READ(code);
	ret = EVAL(ret);
	ret = PRINT(ret);
	return ret;
}

int main(int argc, char **argv) {
	while(1) {
		/* Output our prompt and get input */
		char * input = readline("user> ");
		if (!input) { break; }

		/* Add input to history */
		add_history(input);

		char *output = rep(input);
		printf("%s\n", output);

		free(input);
	}
	return 0;
}
