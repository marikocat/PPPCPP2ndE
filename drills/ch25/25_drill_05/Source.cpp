#include <iomanip>
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	unsigned short int x = 0;
	unsigned short int x1 = ~x;
	cout << "x1: " << dec << x1 << " == " <<
		hex << "0x" << x1 << '\n';
	cout << bitset<16>{x1} << '\n';

	unsigned short int x2 = 1;
	cout << "x2: " << dec << x2 << " == " <<
		hex << "0x" << setw(4) << setfill('0') << x2 << '\n';
	cout << bitset<16>{x2} << '\n';

	unsigned short x3 = x2<<15;
	cout << "x3: " << dec << x3 << " == " <<
		hex << "0x" << x3 << '\n';
	cout << bitset<16>{x3} << '\n';

	unsigned short x4 = x1>>8;
	cout << "x4: " << dec << x4 << " == " <<
		hex << "0x" << setw(4) << setfill('0') << x4 << '\n';
	cout << bitset<16>{x4} << '\n';

	unsigned short x5 = x1<<8;
	cout << "x5: " << dec << x5 << " == " <<
		hex << "0x" << x5 << '\n';
	cout << bitset<16>{x5} << '\n';

	unsigned short x6 = 1;
	for (int i = 0; i < 7; ++i)
	{
		x6<<=2;
		++x6;
	}
	cout << "x6: " << dec << x6 << " == " <<
		hex << "0x" << x6 << '\n';
	cout << bitset<16>{x6} << '\n';

	unsigned short x7 = ~x6;
	cout << "x7: " << dec << x7 << " == " <<
		hex << "0x" << x7 << '\n';
	cout << bitset<16>{x7} << '\n';

}