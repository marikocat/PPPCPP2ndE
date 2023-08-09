#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
	string s = R"(~!@#$%^&*()_+`1234567890-=qwertyuiop[]\QWERTYUIOP{}|asdfghjkl;'ASDFGHJKL:"zxcvbnm,./ZXCVBNM<>?)";
	for (char ch : s)
		cout << ch << ": " << int(ch) << '\n';
	cout << "\n\n";
	sort(s.begin(), s.end(), [](char a, char b) {return a < b; });
	for (char ch : s)
		cout << ch << ": " << int(ch) << '\n';
}