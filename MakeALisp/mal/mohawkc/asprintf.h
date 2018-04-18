#ifndef ASPRINTF_H
#define ASPRINTF_H

#ifndef HAVE_ASPRINTF
int asprintf(char **str, char *fmt, ...);
#endif

#endif
