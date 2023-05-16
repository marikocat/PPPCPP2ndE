#include <iostream>
using namespace std;

string cat_dot(const string& s1, const string& s2)
{
	string res = s1 + '.' + s2;
	return res;
}

int main()
{
	cout << cat_dot("Niels", "Bohr") << '\n';
}