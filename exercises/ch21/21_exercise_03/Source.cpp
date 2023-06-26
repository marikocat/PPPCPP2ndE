#include <iostream>
#include <vector>
using namespace std;

template<typename In, typename T>
int my_count(In first, In last, const T& val)
{
	int res = 0;
	while (first != last)
	{
		if (*first == val) res++;
		++first;
	}
	return res;
}

int main()
{
	vector<double> vd{ 1.1, 2.2, 3.3, 3.3, 4.4, 3.3, 5.5, 6.6, 3.3, 3.0 };
	cout << my_count(vd.begin(), vd.end(), 3.3) << '\n';
}