#include <iostream>
#include <list>
#include <vector>
using namespace std;

template<typename In, typename T>
int my_count(In first, In last, const T& val)
{
	int res = 0;
	while (first != last)
	{
		if (*first++ == val)
			++res;

	}
	if (*first == val)
		++res;
	return res;
}

template<typename In, typename T>
bool my_find(In first, In last, const T& val)
{
	while (first != last && *first != val) ++first;
	if (*first != val && first == last) return false;
	return true;
}

int main()
{
	list<int> li{ 1, 2, 3 ,4 , 3, 5, 6, 3, 7, 9, 8 };
	auto p = li.begin();
	for (int i = 1; i < li.size(); ++i, ++p);
	cout << my_count(li.begin(), p, 3) << '\n';
	auto fp = my_find(li.begin(), p, 10);
	if (fp) cout << "found\n";
	else cout << "not found\n";
}