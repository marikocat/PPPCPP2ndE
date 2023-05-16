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

char to_lower(const char ch)
{
	char res = ch;
	if (ch >= 'A' && ch <= 'Z') res = ch + 32;
	return res;
}

char* str_dup(const char* s, int size)
{
	char* pa = new char[size];
	char* temp = pa;
	while (size)
	{
		*temp = *s;
		++s;
		++temp;
		--size;
	}
	*temp = '\0';
	return pa;
}

char* findx(const char* s, int s_size, const char* x, int x_size)
{
	for (; s_size; ++s, --s_size)
	{
		const char* ts = s;
		int t_ss = s_size;
		int t_xs = x_size;
		for (const char* tx = x; to_lower(*tx) == to_lower(*ts) && t_ss && t_xs; ++ts, --t_ss)
		{
			++tx;
			--t_xs;
			if (!t_xs) return const_cast<char*>(s);
		}
	}
	return nullptr;
}

int str_cmp(const char* s1, int s1_size, const char* s2, int s2_size)
{
	int l1 = s1_size;
	int l2 = s2_size;
	while (s1_size && s2_size)
	{
		if (to_lower(*s1) < to_lower(*s2)) return -1;
		else if (to_lower(*s1) > to_lower(*s2)) return 1;
		++s1;
		++s2;
		--s1_size;
		--s2_size;
	}
	if (l1 == l2) return 0;
	else if (l1 < l2) return -1;
	else return 1;
}

int main()
{
	char s1[] = "Hello";
	char s2[] = { 'H', 'e', 'l', 'l', 'o' };
	char* s3 = new char[]{ 'h', 'a', 'n', 'd' };
	char s4[] = { 'h', 'e', 'l', 'l' };
	cout << str_dup(s3, 4) << '\n';
	char* p = findx(s2, 5, s3, 4);
	if (p)
		cout << p << '\n';
	else
		cout << "not found\n";
	p = findx(s2, 5, s4, 4);
	if (p)
		cout << p << '\n';
	else
		cout << "not found\n";
	cout << str_cmp(s2, 5, s3, 4) << '\n';
}