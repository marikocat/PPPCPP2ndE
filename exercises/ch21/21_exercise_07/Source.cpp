#include <iostream>
#include <list>
#include <vector>
using namespace std;

bool binary_search(vector<int>& v, int val)
{
	int start = 0;
	int end = v.size() - 1;
	while (start <= end)
	{
		int middle = (start + end) / 2;
		if (v[middle] < val)
		{
			start = middle + 1;
		}
		else if (v[middle] > val)
		{
			end = middle - 1;
		}
		else
		{
			return true;
		}
	}
	return false;
}

template<typename Iter, typename T>
bool binary_search2(Iter first, Iter last, const T& val)
{
	int start = 0;
	int end = std::distance(first, last) - 1;
	
	while (start <= end)
	{
		int middle = (start + end) / 2;
		auto p = first;
		std::advance(p, middle);
		if (*p < val)
		{
			start = middle + 1;
		}
		else if (*p > val)
		{
			end = middle - 1;
		}
		else
		{
			return true;
		}
	}
	return false;
}

int main()
{
	vector<int> v{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	if (binary_search(v, 11)) cout << "found in a vector\n";
	else cout << "not found in a vector\n";
	list<int> l{ 1, 3, 4, 5, 6, 7, 8, 9 };
	if (binary_search2(l.begin(), l.end(), 3)) cout << "found in a list\n";
	else cout << "not found in a list\n";
}