#include <iostream>
#include <vector>
using namespace std;

template<typename T, typename U>
T f(const vector<T>& vt, const vector<U>& vu)
{
	T sum = T();
	for (int i = 0; i < vt.size() && i < vu.size(); ++i)
		sum += vt[i] * vu[i];
	return sum;
}

int main()
try
{
	vector<double> vd{ 1, 2, 3, 4, 5 };
	vector<int> vi{ 10, 10, 10, 10, 10 };

	cout << f(vd, vi) << '\n';
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