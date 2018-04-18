#include <stdio.h>

long long int fibonacci()
{
    static long long int first = 0;
    static long long int second = 1;
    long long int out = first+second;
    first=second;
    second=out;
    return out;
}

int main(int argc, char **argv)
{
    for (int i = 0; i < 50; i++) {
        printf("%lli\n", fibonacci());
    }
}