#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *get_string()
{
    int size = 8;
    char *s = (char *)malloc(size);
    if (!s)
    {
        fprintf(stderr, "cannot allocate memory\n");
        exit(1);
    }
    int count = 0;
    int c;
    if ((c = getchar()) == EOF)
        return 0;

    do
    {
        if (count == size - 1)
        {
            size += size;
            s = (char *)realloc(s, size);
            if (!s)
            {
                fprintf(stderr, "cannot reallocate memory\n");
                exit(1);
            }
        }
        s[count++] = c;
    } while ((c = getchar()) != EOF && !isspace(c));
    s[count] = 0;
    return s;
}

int main(void)
{
    for (char *word; word = get_string();)
    {
        printf("%s\n", word);
    }
}