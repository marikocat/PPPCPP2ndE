#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

vector<double> copy_list(const list<int>& l)
{
	vector<double> v;
	for (auto p = l.begin(); p != l.end(); ++p)
		v.push_back(*p);
	sort(v.begin(), v.end());
	return v;
}

int main()
{
	list<int> l = { 5, 4, 3, 2, 1, 0 };
	vector<double> v = copy_list(l);
	for (double d : v) cout << d << ' ';
	cout << '\n';
}