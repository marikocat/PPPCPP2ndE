#include <iostream>
using namespace std;

int main()
{
	int size = 15;
	char* s = new char[size];
	char ch = 0;
	for (int i = 0; cin >> ch; ++i)
	{
		if (ch == '!' || i == size - 1)
		{
			s[i] = '\0';
			break;
		}
		s[i] = ch;
	}
	cout << s << "\n";
}