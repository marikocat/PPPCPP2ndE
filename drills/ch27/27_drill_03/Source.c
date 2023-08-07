#include <stdio.h>

void f(char *p, int x)
{
    printf("p is \"%s\" and x is %d.\n", p, x);
}

int main(void)
{
    f("foo", 7);
}