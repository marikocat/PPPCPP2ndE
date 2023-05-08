#include <iostream>
using namespace std;

void to_lower(char* s)
{
	for (int i = 0; s[i]; ++i)
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] = s[i] + 32;
	}
}

int main()
{
	char s[] = "Hello, World!";
	to_lower(s);
	cout << s << '\n';
}