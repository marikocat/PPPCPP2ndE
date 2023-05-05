#include <iostream>
#include <vector>
using namespace std;

void print_array(ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
		os << a[i] << ' ';
	os << '\n';
}

int main()
{
	int size = 1;
	int* p1 = new int{ 7 };
	cout << "p1 == " << p1 << "; values: ";
	print_array(cout, p1, size);

	size = 7;
	int* p2 = new int[size];
	for (int i = 0; i < size; ++i)
	{
		p2[i] = pow(2, i);
	}
	cout << "p2 == " << p2 << "; values: ";
	print_array(cout, p2, size);

	int* p3 = p2;
	p2 = p1;
	p2 = p3;

	size = 1;
	cout << "p1 == " << p1 << "; values: ";
	print_array(cout, p1, size);
	size = 7;
	cout << "p2 == " << p2 << "; values: ";
	print_array(cout, p2, size);

	delete p1;
	delete[] p2;

	size = 10;
	p1 = new int[size];
	for (int i = 0; i < size; ++i)
		p1[i] = pow(2, i);

	p2 = new int[size];
	for (int i = 0; i < size; ++i)
		p2[i] = p1[i];
	print_array(cout, p2, size);

	vector<int> v1 = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };
	vector<int> v2(size);
	for (int i = 0; i < v1.size(); ++i)
		v2[i] = v1[i];
	for (int i : v2)
		cout << i << ' ';
	cout << '\n';
}