#include <iostream>
#include <vector>
using namespace std;

template<typename T>
void f(vector<T>& v1, const vector<T>& v2)
{
	for (int i = 0; i < v1.size() && i < v2.size(); ++i)
		v1[i] += v2[i];
}

int main()
try
{
	vector<int> v1{ 1, 3, 5, 7, 9 };
	vector<int> v2{ 9, 7, 5, 3, 1 };

	f(v1, v2);

	for (int i : v1)
		cout << i << ' ';
	cout << '\n';
}
catch (exception& e)
{
	cerr << "error: " << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}