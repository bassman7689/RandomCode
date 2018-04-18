#include "operators.h"

int op_add(GArray *children)
{
	int i;
	int ret = 0;
	for(i = 0; i < children->len; i++)
	{
		mal_val *child = g_array_index(children, mal_val*, i);
		ret += child->val.num;
	}

	return ret;
}

int op_sub(GArray *children)
{
	int i;
	int ret = 0;
	if(children->len == 1)
	{
		mal_val *child = g_array_index(children, mal_val*, 0);
		return -child->val.num;
	}
	for(i = 0; i < children->len; i++)
	{
		mal_val *child = g_array_index(children, mal_val*, i);
		if (i == 0)
		{
			ret = child->val.num;
		}
		else
		{
			ret -= child->val.num;
		}
	}

	return ret;
}

int op_mul(GArray *children)
{
	int i;
	int ret = 1;
	for(i = 0; i < children->len; i++)
	{
		mal_val *child = g_array_index(children, mal_val*, i);
		ret *= child->val.num;
	}

	return ret;
}

int op_div(GArray *children)
{
	int i;
	int ret = 0;
	for(i = 0; i < children->len; i++)
	{
		mal_val *child = g_array_index(children, mal_val*, i);
		if (i == 0)
		{
			ret = child->val.num;
		}
		else
		{
			ret /= child->val.num;
		}
	}

	return ret;
}

