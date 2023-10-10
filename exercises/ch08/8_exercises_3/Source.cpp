#include "../std_lib_facilities.h"

void print(const string& label, const vector<int>& v)
{
	cout << label;
	for (int i : v)
		cout << i << " ";
	cout << "\n";
}

void fibonacci(int x, int y, vector<int>& v, int n)
{
	if (n < 2)
		return;
	else
		v.push_back(x);
		for (int i = 1; i < n; i++)
		{
			v.push_back(y);
			y = v[i - 1] + v[i];
		}
}

int main()
{
	vector<int> fibNums;
	fibonacci(1, 2, fibNums, 7);
	print("vector of Fibonacci numbers: ", fibNums);
}