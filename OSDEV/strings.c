#include "strings.h"

void memcpy(unsigned char *dest, const unsigned char *src, unsigned int len)
{
	const unsigned char *sp = (const unsigned char *)src;
	unsigned char *dp = (unsigned char *)dest;
	for(; len != 0; len--) *dp++ = *sp++;
}

void memset(unsigned char *dest, unsigned char val, unsigned int len)
{
	unsigned char *temp = (unsigned char *)dest;
	for ( ; len != 0; len--) *temp++ = val;
}

int strcmp(char *str1, char *str2)
{
	int i = 0;
	int failed = 0;
	while(str1[i] != '\0' && str2[i] != '\0')
	{
		if(str1[i] != str2[i])
		{
			failed = 1;
			break;
		}
		i++;
	}

	if ((str1[i] == '\0' && str2[i] != '\0') || (str1[i] != '\0' && str2[i] == '\0'))
	{
		failed = 1;
	}

	return failed;
}

char *strcpy(char *dest, const char *src)
{
	do
	{
		*dest++ = *src++;
	} while (*src != 0);
	return dest;
}

char *strcat(char *dest, const char *src)
{
	while (*dest != 0)
	{
		dest++;
	}

	do
	{
		*dest++ = *src++;
	} while (*src != 0);
	return dest;
}
