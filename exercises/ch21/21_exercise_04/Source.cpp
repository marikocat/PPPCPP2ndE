#include <iostream>
#include <vector>
using namespace std;

template<typename In, typename Pred>
int my_count_if(In first, In last, Pred p)
{
	int res = 0;
	while (first != last)
	{
		if (p(*first)) res++;
		++first;
	}
	return res;
}

int main()
{
	vector<double> vd{ 1.1, 2.2, 3.3, 3.3, 4.4, 3.3, 5.5, 6.6, 3.3, 3.0 };
	cout << my_count_if(vd.begin(), vd.end(), [](double x) {return x > 3; }) << '\n';
}