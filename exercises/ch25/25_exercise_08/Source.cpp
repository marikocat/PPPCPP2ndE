#include <iostream>
using namespace std;

void print_char(char ch)
{
	cout << ch << ": " << int(ch) << '\n';
}

int main()
{
	for (char ch = 32; ch < 127; ++ch)
		print_char(ch);
}