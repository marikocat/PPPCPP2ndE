#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Pair
{
    const char *s;
    int n;
};

struct Table
{
    struct Pair **pairs;
    int size;
    int space;
};

struct Table *create_table()
{
    struct Table *t = (struct Table *)malloc(sizeof(struct Table));
    if (!t)
    {
        fprintf(stderr, "could not allocate memory for Table of size: %d\n", sizeof(struct Table));
        exit(1);
    }
    t->pairs = 0;
    t->size = 0;
    t->space = 0;
    return t;
}

void destroy_table(struct Table *tbl)
{
    assert(tbl);
    {
        for (int i = 0; i < tbl->size; i++)
            free(tbl->pairs[i]);
        free(tbl);
    }
}

int find(struct Table *tbl, const char *key)
{
    assert(tbl);
    {
        for (int i = 0; i < tbl->size; i++)
            if (key == tbl->pairs[i]->s)
                return i;
        return -1;
    }
}

void resize(struct Table *tbl)
{
    if (tbl->pairs)
    {
        tbl->pairs = (struct Pair **)realloc(tbl->pairs, sizeof(struct Pair *) * tbl->space);
        if (!tbl->pairs)
        {
            fprintf(stderr, "could not allocate memory for Pair pointers of size: %d\n", sizeof(struct Pair *) * tbl->space);
            exit(1);
        }
    }
    else
    {
        tbl->pairs = (struct Pair **)malloc(sizeof(struct Pair *));
        if (!tbl->pairs)
        {
            fprintf(stderr, "could not allocate memory for a Pair pointer of size: %d\n", sizeof(struct Pair *));
            exit(1);
        }
    }
}

void insert(struct Table *tbl, const char *key, int val)
{
    assert(tbl);

    if (find(tbl, key) != -1)
        return;

    struct Pair *p = (struct Pair *)malloc(sizeof(struct Pair));
    p->s = key;
    p->n = val;

    if (tbl->pairs)
    {
        if (tbl->size == tbl->space)
        {
            tbl->space *= 2;
            resize(tbl);
        }
        tbl->size++;
        tbl->pairs[tbl->size - 1] = p;
    }
    else
    {
        if (tbl->space == 0)
        {
            tbl->space = 1;
            resize(tbl);
        }
        tbl->size = 1;
        tbl->pairs[tbl->size - 1] = p;
    }
}

struct Pair *tbl_remove(struct Table *tbl, const char *key)
{
    assert(tbl);

    {
        int i = find(tbl, key);
        if (i == -1)
            return 0;
        struct Pair *temp = tbl->pairs[i];
        tbl->size--;
        for (int k = i; k < tbl->size; k++)
        {
            tbl->pairs[k] = tbl->pairs[k + 1];
        }
        free(temp);
        return tbl->pairs[i];
    }
}

int main()
{
    struct Table *table = create_table();

    insert(table, "hello", 5);
    insert(table, "nice", 2);
    insert(table, "super", 4);
    insert(table, "great", 3);

    for (int i = 0; i < table->size; i++)
        printf("%s: %d\n", table->pairs[i]->s, table->pairs[i]->n);
    printf("\n");

    tbl_remove(table, "hello");

    for (int i = 0; i < table->size; i++)
        printf("%s: %d\n", table->pairs[i]->s, table->pairs[i]->n);
    printf("\n");

    int i = find(table, "great");
    if (i == -1)
        printf("key not found\n");
    else
        printf("%s at index %d with value %d\n", table->pairs[i]->s, i, table->pairs[i]->n);
}