#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *cat(const char *s1, const char *s2)
{
    int sz = strlen(s1) + strlen(s2) + 2;
    char *res = (char *)malloc(sz);
    strcpy(res, s1);
    res[strlen(s1)] = ' ';
    strcpy(res + strlen(s1) + 1, s2);
    res[sz - 1] = '\0';
    return res;
}

int main(void)
{
    char *result = cat("Hello,", "World!");
    printf("%s\n", result);
}