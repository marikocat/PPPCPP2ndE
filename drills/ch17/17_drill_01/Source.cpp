#include <iostream>
#include <vector>
using namespace std;

void print_array10(ostream& os, int* a)
{
	int num = 10;
	for (int i = 0; i < num; ++i)
	{
		os << a[i] << ' ';
	}
	os << '\n';
}

void print_array(ostream& os, int* a, int n)
{
	for (int i = 0; i < n; ++i)
	{
		os << a[i] << ' ';
	}
	os << '\n';
}

void print_vector(ostream& os, const vector<int> v)
{
	for (int i = 0; i < v.size(); ++i)
		os << v[i] << ' ';
	os << '\n';
}

int main()
{
	int num = 10;
	int* ap = new int[]{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i = 0; i < num; ++i)
		cout << ap[i] << ' ';
	cout << '\n';
	print_array10(cout, ap);
	delete[] ap;

	int* arrp = new int[num];
	for (int i = 0; i < num; ++i)
		arrp[i] = 100 + i;
	print_array10(cout, arrp);

	num = 11;
	int* arrp2 = new int[num];
	for (int i = 0; i < num; ++i)
		arrp2[i] = 100 + i;
	print_array(cout, arrp2, num);

	num = 20;
	int* arrp3 = new int[num];
	for (int i = 0; i < num; ++i)
		arrp3[i] = 100 + i;
	print_array(cout, arrp3, num);

	delete[] arrp;
	delete[] arrp2;
	delete[] arrp3;

	num = 10;
	vector<int> v;
	for (int i = 0; i < num; ++i)
		v.push_back(100 + i);
	print_vector(cout, v);

	num = 11;
	vector<int> v2;
	for (int i = 0; i < num; ++i)
		v2.push_back(100 + i);
	print_vector(cout, v2);

	num = 20;
	vector<int> v3;
	for (int i = 0; i < num; ++i)
		v3.push_back(100 + i);
	print_vector(cout, v3);
}