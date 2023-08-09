#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define REINTERPRET_CAST(T, v) ((T)(v))
// This does not give the type checking done by reinterpret_cast and const_cast, but it does make these inherently ugly
// operations visible and the programmer’s intent explicit.

struct Link
{
    int pre;
    int suc;
};

struct List
{
    struct Link **links;
    int first;
    int last;
    int space;
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
    struct List *names = create();

    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Norah")));
    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Annemarie")));
    push_back(names, REINTERPRET_CAST(struct Link *, make_name("Kris")));

    erase(names, names->links[1]);

    int curr = names->first;
    for (; curr <= names->last; curr++)
    {
        printf("element %d: %s\n", curr + 1, (REINTERPRET_CAST(struct Name *, names->links[curr]))->p);
    }
    printf("\n");

    push_front(names, REINTERPRET_CAST(struct Link *, make_name("Kate")));

    curr = names->first;
    for (; curr <= names->last; curr++)
    {
        printf("element %d: %s\n", curr + 1, (REINTERPRET_CAST(struct Name *, names->links[curr]))->p);
    }
    printf("\n");

    insert(names, names->links[2], REINTERPRET_CAST(struct Link *, make_name("Lea")));

    curr = names->first;
    for (; curr <= names->last; curr++)
    {
        printf("element %d: %s\n", curr + 1, (REINTERPRET_CAST(struct Name *, names->links[curr]))->p);
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
    lst->links = 0;
    lst->first = lst->last = 0;
    lst->space = 0;
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
        for (int i = 0; i <= lst->last; i++)
        {
            free(lst->links[i]);
        }
    }
}

void destroy(struct List *lst)
{
    assert(lst);
    clear(lst);
    free(lst);
}

void resize(struct List *lst)
{
    if (lst->links)
    {
        lst->links = (struct Link **)realloc(lst->links, sizeof(struct Link *) * lst->space);
        if (!lst->links)
        {
            fprintf(stderr, "could not allocate space for link pointers of size: %d\n", sizeof(struct Link *) * lst->space);
            exit(1);
        }
    }
    else
    {
        lst->links = (struct Link **)malloc(sizeof(struct Link *));
        if (!lst->links)
        {
            fprintf(stderr, "could not allocate space for a link pointer of size: %d\n", sizeof(struct Link *));
            exit(1);
        }
    }
}

void push_back(struct List *lst, struct Link *p)
{
    assert(lst);
    assert(p);
    {
        if (lst->links)
        {
            if (lst->space == lst->last + 1)
            {
                lst->space *= 2;
                resize(lst);
            }
            lst->last += 1;
            p->pre = lst->last - 1;
            p->suc = lst->last + 1;
            lst->links[lst->last] = p;
        }
        else
        {
            if (lst->space == 0)
            {
                lst->space = 1;
                resize(lst);
            }

            p->pre = -1;
            p->suc = 1;
            lst->first = lst->last = 0;
            lst->links[lst->last] = p;
        }
    }
}

void push_front(struct List *lst, struct Link *p)
{

    if (lst->links)
    {
        insert(lst, lst->links[lst->first], p);
    }
    else
    {
        push_back(lst, p);
    }
}

void insert(struct List *lst, struct Link *p, struct Link *q) // insert q before p in lst
{
    assert(lst);
    assert(p);
    assert(q);
    {
        if (lst->space == lst->last + 1)
        {
            lst->space *= 2;
            resize(lst);
        }

        for (int i = p->suc - 1; i <= lst->last; i++)
        {
            ++lst->links[i]->pre;
            ++lst->links[i]->suc;
        }
        ++lst->last;
        for (int i = lst->last; i > p->pre; i--)
        {
            lst->links[i] = lst->links[i - 1];
        }
        q->pre = p->pre - 1;
        q->suc = p->suc - 1;
        lst->links[p->pre] = q;
    }
}

struct Link *erase(struct List *lst, struct Link *p)
// return a pointer to the link after p
{
    assert(lst);
    if (p == 0)
        return 0;

    for (int i = p->suc; i <= lst->last; i++)
    {
        --lst->links[i]->pre;
        --lst->links[i]->suc;
    }
    --lst->last;
    for (int i = p->suc - 1; i <= lst->last; i++)
    {
        lst->links[i] = lst->links[i + 1];
    }
    int next = p->pre + 1;
    free(p);
    return lst->links[next];
}