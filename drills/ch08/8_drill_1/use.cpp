#include "my.h"

//  As foo is defined as extern in my.h, we must define it in use.cpp in the
//  global scope for print_foo() to have visibility of it.

int foo = 7;

int main()
{
    print_foo();
    print(99);
}