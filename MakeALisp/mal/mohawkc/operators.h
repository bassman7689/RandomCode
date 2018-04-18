#ifndef OPERATORS_H
#define OPERATORS_H

#include <glib.h>
#include "ast.h"

int op_add(GArray *children);
int op_sub(GArray *children);
int op_mul(GArray *children);
int op_div(GArray *children);

#endif
