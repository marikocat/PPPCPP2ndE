#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	int bits_num = 0;
	for (int i = 1; i != 0; i <<= 1)
		++bits_num;
	cout << "size of int is " << bits_num << " bits\n";

	char ch = -1;
	if (ch == -1) cout << "char is signed\n";
	else cout << "char is unsigned\n";

	char ch1 = -1;
	cout << int(ch1);
	unsigned char ch2 = -1;
	cout << "\n" << int(ch2) << "\n";

	int si = -1;
	cout << bitset<32> {unsigned(si)} << '\n';
	char c = si;
	unsigned char uc = si;
	signed char sc = si;
	cout << int(c) << ' ' << int(uc) << "\n";
	if (c == sc) cout << "char is signed\n";
}