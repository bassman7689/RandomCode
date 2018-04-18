#ifndef EVAL_H
#define EVAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>
#include "env.h"
#include "ast.h"


mal_val *eval_ast(mal_val *ast, Env *env);
mal_val *EVAL(mal_val *ast, Env *env);
#endif
