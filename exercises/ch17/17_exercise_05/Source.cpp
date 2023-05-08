#include <iostream>
using namespace std;

char* findx(const char* s, const char* x)
{
	for (int i = 0; s[i]; ++i)
		for (int j = 0; s[i + j] == x[j];)
		{
			++j;
			if (!x[j]) return const_cast<char*>(&s[i]);
		}
	return nullptr;
}

int main()
{
	char s1[] = "hello, world!";
	char s2[] = "world";
	char* p = findx(s1, s2);
	cout << s1 << '\n' << p << '\n';

	printf("%p\n", s1);
	printf("%p\n", p);
}