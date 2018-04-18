#ifndef STRINGS_H
#define STRINGS_H

void memcpy(unsigned char *dest, const unsigned char *src, unsigned int len);
void memset(unsigned char *dest, unsigned char val, unsigned int len);
int strcmp(char *str1, char *str2);
char *strcpy(char *dest, const char *src);
char *strcat(char *dest, const char *src);

#endif
