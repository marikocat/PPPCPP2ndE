#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define REINTERPRET_CAST(T, v) ((T)(v))
// This does not give the type checking done by reinterpret_cast and const_cast, but it does make these inherently ugly
// operations visible and the programmer’s intent explicit.

struct Link
{
    struct Link *pre;
    struct Link *suc;
};

struct List
{
    struct Link *first;
    struct Link *last;
};

struct Name
{
    struct Link lnk;
    char *p;
};

void init(struct List *lst);
struct List *create();
void clear(struct List *lst);
void destroy(struct List *p);

void push_back(struct List *lst, struct Link *p);
void push_front(struct List *lst, struct Link *p);

void insert(struct List *lst, struct Link *p, struct Link *q); // insert q before p in lst
struct Link *erase(struct List *lst, struct Link *p);          // remove p from list

struct Link *advance(struct Link *p, int n); // return link n "hops" before or after p

struct Name *make_name(char *n);

int main()
{
    int count = 0;
    struct List *names = create();
    struct Link *curr;

    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Norah")));
    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Annemarie")));
    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Kris")));

    erase(names, advance(names->first, 1));

    curr = names->first;
    for (; curr != 0; curr = curr->suc)
    {
        count++;
        printf("element %d: %s\n", count, (REINTERPRET_CAST(struct Name *, curr))->p);
    }
    printf("\n");

    push_front(names, REINTERPRET_CAST(struct Link *, make_name("Kate")));

    curr = names->first;
    count = 0;
    for (; curr != 0; curr = curr->suc)
    {
        count++;
        printf("element %d: %s\n", count, (REINTERPRET_CAST(struct Name *, curr))->p);
    }
    printf("\n");

    insert(names, advance(names->first, 2), REINTERPRET_CAST(struct Link *, make_name("Lea")));

    curr = names->first;
    count = 0;
    for (; curr != 0; curr = curr->suc)
    {
        count++;
        printf("element %d: %s\n", count, (REINTERPRET_CAST(struct Name *, curr))->p);
    }
    printf("\n");
}

struct Name *make_name(char *n)
{
    struct Name *p = (struct Name *)malloc(sizeof(struct Name));
    if (!p)
    {
        fprintf(stderr, "could not allocate struct Name of size: %d\n", sizeof(struct Name));
        exit(1);
    }
    p->p = n;
    return p;
}

void init(struct List *lst) // initilize *lst to the empty list
{
    assert(lst);
    lst->first = lst->last = 0;
}

struct List *create()
{
    struct List *lst = (struct List *)malloc(sizeof(struct List));
    if (!lst)
    {
        fprintf(stderr, "could not allocate struct List of size: %d\n", sizeof(struct List));
        exit(1);
    }
    init(lst);
    return lst;
}

void clear(struct List *lst)
{
    assert(lst);
    {
        struct Link *curr = lst->first;
        while (curr)
        {
            struct Link *next = curr->suc;
            free(curr);
            curr = next;
        }
        lst->first = lst->last = 0;
    }
}

void destroy(struct List *lst)
{
    assert(lst);
    clear(lst);
    free(lst);
}

void push_back(struct List *lst, struct Link *p)
{
    assert(lst);
    assert(p);
    {
        struct Link *last = lst->last;
        if (last)
        {
            last->suc = p;
            p->pre = last;
        }
        else
        {
            lst->first = p;
            p->pre = 0;
        }
        lst->last = p;
        p->suc = 0;
    }
}

void push_front(struct List *lst, struct Link *p)
{
    assert(lst);
    assert(p);
    {
        struct Link *first = lst->first;
        if (first)
        {
            first->pre = p;
            p->suc = first;
        }
        else
        {
            lst->last = p;
            p->suc = 0;
        }
        lst->first = p;
        p->pre = 0;
    }
}

void insert(struct List *lst, struct Link *p, struct Link *q) // insert q before p in lst
{
    assert(lst);
    assert(p);
    assert(q);
    {
        if (p->pre)
        {
            q->suc = p;
            q->pre = p->pre;
            q->pre->suc = q;
            p->pre = q;
        }
        else
        {
            q->suc = p;
            q->pre = 0;
            p->pre = q;
            lst->first = q;
        }
    }
}

struct Link *erase(struct List *lst, struct Link *p)
// return a pointer to the link after p
{
    assert(lst);
    if (p == 0)
        return 0;

    if (p == lst->first)
    {
        if (p->suc)
        {
            lst->first = p->suc;
            p->suc->pre = 0;
            return p->suc;
        }
        else
        {
            lst->first = lst->last = 0;
            return 0;
        }
    }
    else if (p == lst->last)
    {
        if (p->pre)
        {
            lst->last = p->pre;
            p->pre->suc = 0;
            return 0;
        }
        else
        {
            lst->first = lst->last = 0;
            return 0;
        }
    }
    else
    {
        p->suc->pre = p->pre;
        p->pre->suc = p->suc;
        return p->suc;
    }
}

struct Link *advance(struct Link *p, int n) // return link n "hops" before or after p
{
    assert(p);
    if (n > 0)
    {
        while (n > 0)
        {
            if (p->suc)
                p = p->suc;
            else
                return 0;
            n--;
        }
    }
    else
    {
        while (n < 0)
        {
            if (p->pre)
                p = p->pre;
            else
                return 0;
            n++;
        }
    }
    return p;
}