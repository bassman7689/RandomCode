#ifndef ENV_H
#define ENV_H

#include <string.h>
#include <stdlib.h>
#include <glib.h>
#include "operators.h"
#include "ast.h"

typedef struct Env {
	struct Env *parent;
	GHashTable *data;
} Env;

Env *env_new();
void env_destroy();
Env *build_default_env();
void env_set(Env *env, char *symbol, mal_val *val);
Env *env_find(Env *env, char *symbol);
mal_val *env_get(Env *env, char *symbol);

#endif
