#include <iomanip>
#include <iostream>
#include <bitset>
#include <vector>
using namespace std;

int main()
{
	vector<int> vsi;
	vsi.push_back(0);
	vsi.push_back(0xffffffff);
	int x = 1;
	for (int i = 0; i < 15; ++i)
	{
		x <<= 2;
		++x;
	}
	vsi.push_back(x);
	vsi.push_back(~x);
	x = 3;
	for (int i = 0; i < 7; ++i)
	{
		x <<= 4;
		x += 3;
	}
	vsi.push_back(x);
	vsi.push_back(~x);

	vector<unsigned int> vui;
	for (int si : vsi)
	{
		cout << bitset<sizeof(int) * 8>{unsigned(si)} << " == " << si << '\n';
		vui.push_back(si);
	}

	for (unsigned int ui : vui)
	{
		cout << bitset<sizeof(int) * 8>{ui} << " == " << ui << '\n';
	}
}