#include <iostream>
using namespace std;

int strlength(const char* s)
{
	int length = 0;
	while (*s)
	{
		++length;
		++s;
	}
	return length;
}

char* str_dup(const char* s)
{
	char* pa = new char[strlength(s)];
	char* temp = pa;
	while (*s)
	{
		*temp = *s;
		++s;
		++temp;
	}
	*temp = '\0';
	return pa;
}

int main()
{
	char ss[] = "Hello";
	cout << str_dup(ss) << '\n';
}