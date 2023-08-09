#include <stdio.h>

size_t my_strlen(const char *s)
{
    size_t res = 0;
    while (*s++ != 0)
        res++;
    return res;
}

int my_strcmp(const char *s1, const char *s2)
{
    while (*s1 && *s2)
    {
        if (*s1 != *s2)
            return (*s1 < *s2) ? -1 : 1;
        s1++;
        s2++;
    }

    if (*s1)
        return 1;
    else if (*s2)
        return -1;
    else
        return 0;
}

char *my_strcpy(char *s1, const char *s2)
{
    char *res = s1;
    while (*s2)
    {
        *s1 = *s2;
        s1++;
        s2++;
    }
    *s1 = '\0';
    return res;
}

int main(void)
{
    const char *s1 = "hello";
    printf("%d\n", my_strlen(s1));

    const char *s2 = "hello world";
    if (my_strcmp(s1, s2) == 0)
    {
        printf("strings are equal\n");
    }
    else if (my_strcmp(s1, s2) < 0)
    {
        printf("s1 is lexicographically first\n");
    }
    else
    {
        printf("s2 is lexicographically first\n");
    }

    char s3[6];
    my_strcpy(s3, s1);
    printf("%s\n", s3);
}