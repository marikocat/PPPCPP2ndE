#include <iostream>
#include <list>
#include <vector>
using namespace std;

template<typename Iter1, typename Iter2>
Iter2 my_copy(Iter1 f1, Iter1 e1, Iter2 f2)
{
	for (; f1 != e1; ++f1)
	{
		*f2 = *f1;
		++f2;
	}

	return f2;
}

int main()
{
	const int n = 10;
	int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	vector<int> v = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	list<int> l = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	int arr2[n];
	copy(arr, &arr[n], arr2);
	vector<int> v2 = v;
	list<int> l2 = l;

	for (int i = 0; i < n; ++i)
		arr[i] += 2;
	for (int i = 0; i < v.size(); ++i)
		v[i] += 3;
	for (auto p = l.begin(); p != l.end(); ++p)
		*p += 5;

	vector<int> v3(10);
	my_copy(arr, &arr[n], v3.begin());
	for (int i : v3) cout << i << ' ';
	cout << "copied from arr to v3\n";

	list<int> l3(10);
	my_copy(arr, &arr[n], l3.begin());
	for (int i : l3) cout << i << ' ';
	cout << "copied from arr to l3\n";

	int arr3[n];
	my_copy(l.begin(), l.end(), arr3);
	for (int i = 0; i < n; ++i) cout << arr3[i] << ' ';
	cout << "copied from l to arr3\n";

	for (int i : v) cout << i << ' ';
	cout << "find 5 for v\n";
	auto p = find(v.begin(), v.end(), 5);
	if (p != v.end()) cout << "position: " << p - v.begin() << '\n';
	else cout << "not found\n";

	for (int i : l) cout << i << ' ';
	cout << "find 7 for l\n";
	auto p2 = find(l.begin(), l.end(), 7);
	if (p2 != l.end())
	{
		int i = 0;
		for (auto pp = l.begin(); pp != p2; ++pp, ++i);
		cout << "position: " << i << '\n';
	}
	else cout << "not found\n";
}