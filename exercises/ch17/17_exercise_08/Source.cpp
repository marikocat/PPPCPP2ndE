#include <iostream>
#include <string>
using namespace std;

int main()
{
	string s;
	char ch = 0;
	for (int i = 0; cin >> ch; ++i)
	{
		if (ch == '!')
		{
			break;
		}
		s.push_back(ch);
	}
	cout << s << "\n";
}