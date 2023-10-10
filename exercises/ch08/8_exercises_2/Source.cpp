#include "../std_lib_facilities.h"

void print(const string& label, const vector<int>& v)
{
	cout << label;
	for (int i : v)
		cout << i << " ";
	cout << "\n";
}

int main()
{
	vector<int> v = { 1, 2, 3, 4, 5 };
	print("vector of ints: ", v);
}