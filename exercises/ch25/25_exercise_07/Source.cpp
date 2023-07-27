#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
	for (int i = 0; i <= 400; ++i)
		cout << "0x" << setw(4) << setfill('0') << hex << i << '\n';

	for (int i = -200; i <= 200; ++i)
		cout << "0x" << setw(8) << setfill('0') << hex << i << '\n';
}