#include "../std_lib_facilities.h"

void f()
{
	int n, d;
	cout << "enter to integers: ";
	cin >> n >> d;
	vector<int> v(n + 1);
	for (int i = 0; i < d; ++i)
	{
		++v[randint(n)];
	}

	for (int i = 0; i < v.size(); ++i)
	{
		cout << i << ": ";
		for (int j = 0; j < v[i]; ++j)
			cout << "*";
		cout << '\n';
	}
	cout << '\n';
}

int main()
{
	f();
}