#include <iostream>
using namespace std;

const int max_n = 10;
int ga[] = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void f(const int a[], int n)
{
	int la[max_n];
	for (int i = 0; i < max_n; ++i)
	{
		la[i] = ga[i];
	}
	for (int i : la)
		cout << i << ' ';
	cout << '\n';
	int* p = new int[n];
	for (int i = 0; i < n; ++i)
	{
		p[i] = a[i];
		cout << p[i] << ' ';
	}
	cout << '\n';
	delete[] p;
}

int main()
{
	f(ga, max_n);

	int aa[max_n];
	for (int i = 0; i < max_n; ++i)
	{
		if (i == 0)
			aa[i] = i + 1;
		else
			aa[i] = (i + 1) * aa[i - 1];
	}
	f(aa, max_n);
}