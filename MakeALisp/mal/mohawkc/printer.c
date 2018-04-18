#include "printer.h"

static void __print_str(mal_val *ast)
{
	if(ast == NULL)
	{
		return;
	}

	switch(ast->type) {
		case MAL_ERROR:
			printf("%s", ast->val.message);
			break;

		case MAL_LIST: {
			putchar('(');
			int i;
			for(i = 0; i < ast->val.children->len; i++)
			{
				__print_str(g_array_index(ast->val.children, mal_val*, i));
				if (i < ast->val.children->len - 1)
				{
					putchar(' ');
				}
			}
			putchar(')');
			break;
		}

		case MAL_NUMBER:
			printf("%ld", ast->val.num);
			break;

		case MAL_SYMBOL:
			printf("%s\n", ast->val.symbol);
			break;

		case MAL_NIL:
			printf("%s", "nil");
			break;

		case MAL_TRUE:
			printf("%s", "true");
			break;

		case MAL_FALSE:
			printf("%s", "false");
			break;

		default:
			fprintf(stderr, "Error: Invalid Type\n");
	}
}

void print_str(mal_val *ast)
{
	__print_str(ast);
	putchar('\n');
}

void PRINT(mal_val *ast) {
	print_str(ast);
}

