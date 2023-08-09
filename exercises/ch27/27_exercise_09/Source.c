#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define ARR_SIZE 5
#define WORD_LEN 32

int compare_strings(const void *a, const void *b)
{
    const char *aa = *(const char **)a;
    const char *bb = *(const char **)b;
    return strcmp(aa, bb);
}

int main()
{
    char *words[ARR_SIZE] = {0};

    for (int j = 0; j < ARR_SIZE; j++)
    {
        char ch;
        int i;
        char *buffer = (char *)malloc(sizeof(char) * WORD_LEN);
        for (i = 0; i < WORD_LEN - 1 && (ch = getchar()) != EOF && !isspace(ch); i++)
        {
            buffer[i] = ch;
        }
        buffer[i] = 0;
        words[j] = buffer;
    }

    printf("\n");
    for (int j = 0; j < ARR_SIZE; j++)
    {
        printf("%s\n", words[j]);
    }

    qsort(words, ARR_SIZE, sizeof(char *), compare_strings);
    printf("\n");
    for (int j = 0; j < ARR_SIZE; j++)
    {
        printf("%s\n", words[j]);
        free(words[j]);
    }
}