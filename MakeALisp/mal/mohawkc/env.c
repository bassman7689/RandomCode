#include "env.h"

void mal_val_free_env(void *val)
{
	mal_val_free((mal_val*)val);
}

Env *env_new()
{
	Env *ret = malloc(sizeof(Env));
	ret->data = g_hash_table_new_full(g_str_hash, g_str_equal, g_free, mal_val_free_env);
	ret->parent = NULL;

	return ret;
}

void env_destroy(Env *env)
{
	if(env == NULL)
	{
		return;
	}
	if(env->data != NULL)
	{
		g_hash_table_destroy(env->data);
	}
	free(env);
}

Env *build_default_env()
{
	Env *env = env_new();
	env_set(env, strdup("+"), mal_val_new_op(op_add));
	env_set(env, strdup("-"), mal_val_new_op(op_sub));
	env_set(env, strdup("*"), mal_val_new_op(op_mul));
	env_set(env, strdup("/"), mal_val_new_op(op_div));
	return env;
}


void env_set(Env *env, char *symbol, mal_val *val)
{
	g_hash_table_insert(env->data, g_strdup(symbol), mal_val_dup(val));
}

Env *env_find(Env *env, char *symbol)
{
	mal_val *ret;
	ret = g_hash_table_lookup(env->data, symbol);
	if(ret == NULL && env->parent != NULL)
	{
		return env_find(env->parent, symbol);
	}
	else if(ret == NULL)
	{
		return NULL;
	}
	else
	{
		return env;
	}
}

mal_val *env_get(Env *env, char *symbol)
{
	Env *container = env_find(env, symbol);

	if(container == NULL)
	{
		return NULL;
	}

	return g_hash_table_lookup(container->data, symbol);
}
