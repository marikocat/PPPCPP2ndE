#include <iostream>
using namespace std;

char* str_dup(const char* s)
{
	int size = 0;
	for (; s[size]; ++size);
	char* sp = new char[++size];
	for (int i = 0; i < size; ++i)
		sp[i] = s[i];
	return sp;
}

int main()
{
	char s[] = "Hello, World!";
	char* p = str_dup(s);
	for (int i = 0; p[i]; ++i)
		cout << p[i];
	cout << '\n';

	delete[] p;
}