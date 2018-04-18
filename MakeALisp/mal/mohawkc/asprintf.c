#ifndef HAVE_ASPRINTF
#ifndef _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "asprintf.h"

int asprintf(char **str, char *fmt, ...)
{
	va_list argp;

	va_start(argp, fmt);
	char one_char[1];
	int len = vsnprintf(one_char, 1, fmt, argp);
	if (len < 1)
	{
		*str = NULL;
		return len;
	}
	va_end(argp);

	*str = malloc(len+1);
	if(!str)
	{
		return -1;
	}

	va_start(argp, fmt);
	vsnprintf(*str, len+1, fmt, argp);
	va_end(argp);

	return len;
}

#endif
#endif
