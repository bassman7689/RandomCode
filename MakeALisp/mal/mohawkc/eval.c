#include "eval.h"

const char *def = "def!";
const char *let = "let*";

mal_val *eval_ast(mal_val *ast, Env *env)
{
	if(ast == NULL)
	{
		return NULL;
	}
	switch(ast->type) {
		case MAL_SYMBOL: {
			mal_val *op = (mal_val*)env_get(env, ast->val.symbol);
			if (op == NULL) {
				char *error;
				asprintf(&error, "'%s' not found.", ast->val.symbol);
				mal_val *err = mal_val_new_error(error);
				free(error);
				return err;
			}
			return mal_val_dup(op);
		}
		case MAL_LIST: {
			int i;
			for(int i = 0; i < ast->val.children->len;i++)
			{
				mal_val *child = g_array_index(ast->val.children, mal_val*, i);
				
				mal_val *new_val = EVAL(child, env);

				if(new_val->type == MAL_ERROR)
				{
					return new_val;
				}
				g_array_index(ast->val.children, mal_val*, i) = new_val;
			}
			return ast;
		}
		default:
			return ast;
	}
}

mal_val *EVAL(mal_val *ast, Env *env) {
	if(ast == NULL)
	{
		return NULL;
	}

	else if (ast->type == MAL_LIST)
	{
		if(ast->val.children == NULL || ast->val.children->len == 0)
		{
			return ast;
		}

		mal_val *op_child = g_array_index(ast->val.children, mal_val*, 0);

		if(op_child->type == MAL_SYMBOL && strncmp(op_child->val.symbol, def, strlen(def)) == 0 && ast->val.children->len == 3)
		{
			mal_val* key = g_array_index(ast->val.children, mal_val*, 1);
			if(key->type != MAL_SYMBOL)
			{
				char *error;
				// NOTE: change this from foo when print_str renders a string
				// instead of printing
				asprintf(&error, "\"%s\" is not a variable name.", "foo");
				mal_val *err = mal_val_new_error(error);
				free(error);
				return err;
			}

			mal_val* val = g_array_index(ast->val.children, mal_val*, 2);
			val = EVAL(val, env);
			if (val->type == MAL_ERROR)
			{
				return val;
			}
			env_set(env, key->val.symbol, val);
			return val;
		}
		else if(op_child->type == MAL_SYMBOL && strncmp(op_child->val.symbol, let, strlen(let)) == 0)
		{
			mal_val *binding_list = g_array_index(ast->val.children, mal_val*, 1);

			if(binding_list->type == MAL_ERROR)
			{
				return binding_list;
			}

			if(binding_list->type != MAL_LIST || binding_list->val.children == NULL || binding_list->val.children->len % 2 != 0)
			{
				return mal_val_new_error("Wrong number of arguments to let*.");
			}
			Env *new_env = env_new();
			new_env->parent = env;

			int i;
			for (i = 0; i < binding_list->val.children->len; i+=2)
			{
				mal_val *first = g_array_index(binding_list->val.children, mal_val*, i);
				mal_val *second = g_array_index(binding_list->val.children, mal_val*, i+1);
				if(first->type == MAL_ERROR)
				{
					return first;
				}
				if(second->type == MAL_ERROR)
				{
					return second;
				}

				second = EVAL(second, new_env);
				if(second->type == MAL_ERROR)
				{
					return second;
				}

				if(first->type == MAL_ERROR)
				{
					return first;
				}
				else if(first->type != MAL_SYMBOL || first->val.symbol == NULL)
				{
					fprintf(stderr, "%d\n", ast->type);
					exit(1);
				}

				env_set(new_env, first->val.symbol, second);
			}
			
			mal_val* third = g_array_index(ast->val.children, mal_val*, 2);
			ast = EVAL(third, new_env);
			env_destroy(new_env);
			return ast;
		}
		else
		{

			ast = eval_ast(ast, env);
			if(ast->type == MAL_ERROR)
			{
				return ast;
			}
			if(ast->type != MAL_LIST)
			{
				return ast;
			}
			if(ast->val.children->len < 3)
			{
				return ast;
			}
			op_child = g_array_index(ast->val.children, mal_val*, 0);
			g_array_remove_index(ast->val.children, 0);
			if(op_child->type == MAL_ERROR)
			{
				return op_child;
			}
			mal_val *ret = mal_val_new_integer(op_child->val.func(ast->val.children));
			mal_val_free(ast);
			return ret;
		}
	}

	else
	{
		return eval_ast(ast, env);
	}
}

