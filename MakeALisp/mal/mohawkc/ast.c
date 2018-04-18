#include "ast.h"

mal_val *mal_val_true;
mal_val *mal_val_false;
mal_val *mal_val_nil;

mal_val *mal_val_new(mal_types type)
{
	mal_val *ret;
	ret = malloc(sizeof(mal_val));
	ret->type = type;
	return ret;
}

mal_val *mal_val_dup(mal_val *mval)
{
	mal_val *ret = malloc(sizeof(mal_val));
	memcpy(ret, mval, sizeof(mal_val));
	return ret;

}

void mal_val_free(mal_val *mval)
{
	if(mval == NULL)
	{
		return;
	}
	if(mval->type == MAL_LIST)
	{
		if(mval->val.children)
		{
			int i;
			for (i = 0; i < mval->val.children->len; i++)
			{
				mal_val_free(g_array_index(mval->val.children, mal_val*, i));
			}
			g_array_free(mval->val.children, FALSE);
		}
	}

	if(mval->type == MAL_SYMBOL)
	{
		if(mval->val.symbol)
		{
			g_free(mval->val.symbol);
		}
	}

	if(mval->type == MAL_ERROR)
	{
		if(mval->val.message)
		{
			g_free(mval->val.message);
		}
	}

	if(mval)
	{
		free(mval);
	}
}

mal_val *mal_val_new_integer(long int val)
{
	mal_val *ret;
	ret = mal_val_new(MAL_NUMBER);
	ret->val.num = val;
	return ret;
}

mal_val *mal_val_new_list(GArray *children)
{
	mal_val *ret;
	ret = mal_val_new(MAL_LIST);
	ret->val.children = children;
	return ret;
}

mal_val *mal_val_new_symbol(char *symbol)
{
	mal_val *ret;
	ret = mal_val_new(MAL_SYMBOL);
	ret->val.symbol = strdup(symbol);
	return ret;
}

mal_val *mal_val_new_op(op_func op)
{
	mal_val *ret;
	ret = mal_val_new(MAL_OP);
	ret->val.func = op;
	return ret;
}

mal_val *mal_val_new_error(char *message)
{
	mal_val *ret;
	ret = mal_val_new(MAL_ERROR);
	ret->val.message = strdup(message);
	return ret;
}

mal_val *mal_val_new_nil()
{
	if (mal_val_nil == NULL)
	{
		mal_val_nil = mal_val_new(MAL_NIL);
	}
	return mal_val_nil;
}

mal_val *mal_val_new_true()
{
	if (mal_val_true == NULL)
	{
		mal_val_true = mal_val_new(MAL_TRUE);
	}
	return mal_val_true;
}

mal_val *mal_val_new_false()
{
	if (mal_val_false == NULL)
	{
		mal_val_false = mal_val_new(MAL_FALSE);
	}
	return mal_val_false;;
}
