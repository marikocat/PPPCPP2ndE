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

char* findx(const char* s, const char* x)
{
	for (; *s; ++s)
	{
		const char* ts = s;
		for (const char* tx = x; *tx == *ts && *ts; ++ts)
		{
			++tx;
			if (!*tx) return const_cast<char*>(s);
		}
	}
	return nullptr;
}

int main()
{
	char ss[] = "hey, hello world!";
	char xx[] = "hello";
	cout << findx(ss, xx) << '\n';
}