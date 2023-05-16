#include <iostream>
using namespace std;

int strlength(const char* s)
{
	int length = 0;
	while (*s)
	{
		++s;
		++length;
	}
	return length;
}

char* cat_dot(const char* s1, const char* s2, const char* separator)
{
	int new_size = strlength(s1) + strlength(s2) + strlength(separator) + 1;
	char* res = new char[new_size];
	char* new_s = res;
	for (; *s1; ++s1)
	{
		*res = *s1;
		++res;
	}
	for (; *separator; ++separator)
	{
		*res = *separator;
		++res;
	}
	for (; *s2; ++s2)
	{
		*res = *s2;
		++res;
	}
	*res = '\0';
	return new_s;
}

char* cat_dot(const char* s1, const char* s2)
{
	return cat_dot(s1, s2, ".");
}

int main()
{
	char* p = cat_dot("Niels", "Bohr");
	cout << p << '\n';
	delete[] p;
	p = cat_dot("Niels", "Bohr", " ");
	cout << p << '\n';
	delete[] p;
}