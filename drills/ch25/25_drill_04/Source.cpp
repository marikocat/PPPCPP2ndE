#include <iostream>
#include <bitset>
#include <iomanip>
using namespace std;

int main()
{
	unsigned short int x = 0xffff;
	cout << sizeof(x) * 8 << '\n';
	cout << "x: " << dec << x << " == " <<
		hex << "0x" << x << '\n';
	cout << bitset<16>{x} << '\n';
	unsigned short int x2 = 0x1;
	cout << "x2: " << dec << x2 << " == " <<
		hex << "0x" << setw(4) << setfill('0') << x2 << '\n';
	cout << bitset<16>{x2} << '\n';
	unsigned short x3 = 0x8000;
	cout << "x3: " << dec << x3 << " == " <<
		hex << "0x" << x3 << '\n';
	cout << bitset<16>{x3} << '\n';
	unsigned short x4 = 0x00ff;
	cout << "x4: " << dec << x4 << " == " <<
		hex << "0x" << setw(4) << setfill('0') << x4 << '\n';
	cout << bitset<16>{x4} << '\n';
	unsigned short x5 = 0xff00;
	cout << "x5: " << dec << x5 << " == " <<
		hex << "0x" << x5 << '\n';
	cout << bitset<16>{x5} << '\n';
	unsigned short x6 = 0x5555;
	cout << "x6: " << dec << x6 << " == " <<
		hex << "0x" << x6 << '\n';
	cout << bitset<16>{x6} << '\n';
	unsigned short x7 = 0xaaaa;
	cout << "x7: " << dec << x7 << " == " <<
		hex << "0x" << x7 << '\n';
	cout << bitset<16>{x7} << '\n';
}