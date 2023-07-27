#include <iostream>
#include <bitset>
using namespace std;

struct PPN
{
	unsigned int PFN : 22; // Page Frame Number
	int : 3; // unused
	unsigned int CCA : 3; // Cache Coherency Algorithm
	bool nonreachable : 1;
	bool dirty : 1;
	bool valid : 1;
	bool global : 1;
};

void print_PPN(const PPN& p)
{
	cout << "PFN: " << p.PFN << ' ' << bitset<22>{p.PFN} <<
		"\nCCA: " << p.CCA << ' ' << bitset<3>{p.CCA} <<
		"\nnonreachable: " << boolalpha << p.nonreachable << ' ' << bitset<1>{p.nonreachable} <<
		"\ndirty: " << boolalpha << p.dirty << ' ' << bitset<1>{p.dirty} <<
		"\nvalid: " << boolalpha << p.valid << ' ' << bitset<1>{p.valid} <<
		"\nglobal: " << boolalpha << p.global << ' ' << bitset<1>{p.global} << '\n';
}


void print_PPN(const unsigned int ui)
{
	unsigned int temp = ui >> 10;
	cout << "PFN: " << temp << ' ' << bitset<22>{temp};
	temp = (ui >> 4) & 7;
	cout << "\nCCA: " << temp << ' ' << bitset<3>{temp};
	temp = (ui >> 3) & 1;
	cout << "\nnonreachable: " << boolalpha << bool(temp) << ' ' << bitset<1>{temp};
	temp = (ui >> 2) & 1;
	cout << "\ndirty: " << boolalpha << bool(temp) << ' ' << bitset<1>{temp};
	temp = (ui >> 1) & 1;
	cout << "\nvalid: " << boolalpha << bool(temp) << ' ' << bitset<1>{temp};
	temp = ui & 1;
	cout << "\nglobal: " << boolalpha << bool(temp) << ' ' << bitset<1>{temp} << '\n';
}

void print_PPN(const bitset<32>& bs)
{
	bitset<32> temp = bs >> 10;
	cout << "PFN: " << temp.to_ulong() << ' ' << bitset<22>{temp.to_ulong()} << '\n';
	temp = (bs >> 4) & bitset<32>{7};
	cout << "CCA: " << temp.to_ulong() << ' ' << bitset<3>{temp.to_ulong()} << '\n';
	temp = (bs >> 3) & bitset<32>{1};
	cout << "nonreachable: " << boolalpha << bool(temp.to_ulong()) << ' ' << bitset<1>{temp.to_ulong()} << '\n';
	temp = (bs >> 2) & bitset<32>{1};
	cout << "dirty: " << boolalpha << bool(temp.to_ulong()) << ' ' << bitset<1>{temp.to_ulong()} << '\n';
	temp = (bs >> 1) & bitset<32>{1};
	cout << "valid: " << boolalpha << bool(temp.to_ulong()) << ' ' << bitset<1>{temp.to_ulong()} << '\n';
	temp = bs & bitset<32>{1};
	cout << "global: " << boolalpha << bool(temp.to_ulong()) << ' ' << bitset<1>{temp.to_ulong()} << '\n';
}

int main()
{
	PPN ppn{ 150, 7, 1, 0, 1, 0 };
	print_PPN(ppn);

	ppn.PFN = 2020;
	ppn.CCA = 5;
	ppn.nonreachable = false;
	ppn.dirty = true;
	ppn.valid = false;
	ppn.global = true;
	print_PPN(ppn);

	unsigned int ppn2 = bitset<32>{ "00000000000111111001000001010101" }.to_ulong();
	print_PPN(ppn2);

	bitset<32> b{ "00000000000111111001000001010101" };
	print_PPN(b);
}