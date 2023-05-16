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

int str_cmp(const char* s1, const char* s2)
{
	int l1 = strlength(s1);
	int l2 = strlength(s2);
	while (*s1 && *s2)
	{
		if (*s1 < *s2) return -1;
		else if (*s1 > *s2) return 1;
		++s1;
		++s2;
	}
	if (l1 == l2) return 0;
	else if (l1 < l2) return -1;
	else return 1;
}

int main()
{
	char s1[] = "let";
	char s2[] = "let";
	int res = str_cmp(s1, s2);
	if (res == 0)
		cout << "s1 equals s2\n";
	else if (res < 0)
		cout << "s1 is lexicographically before s2\n";
	else
		cout << "s1 is lexicographically after s2\n";
}