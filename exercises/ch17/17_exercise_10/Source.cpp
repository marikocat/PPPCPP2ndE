#include <iostream>
using namespace std;

int main()
{
	int size = 10;
	char* s = new char[size];
	char ch = 0;
	for (int i = 0; cin >> ch; ++i)
	{
		if (i == size)
		{
			size *= 2;
			char* temp = new char[size];
			for (int j = 0; j < size / 2; ++j)
				temp[j] = s[j];
			delete[] s;
			s = temp;
		}
		if (ch == '!')
		{
			s[i] = '\0';
			break;
		}
		s[i] = ch;
	}
	cout << s << "\n";
}