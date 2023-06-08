#include <iostream>
#include <vector>
using namespace std;

template<typename Iter>
Iter last_string(Iter first, Iter last)
{
	Iter res = first;
	for (Iter p = first; p != last; ++p)
	{
		if (*res < *p) res = p;
	}
	return res;
}

int main()
{
	vector<string> vs = { "hello", "bye", "goodbye", "hi", "goodnight" };
	auto p = last_string(vs.begin(), vs.end());
	if (p != vs.end())
		cout << "The lexicographical last string is " << *p << '\n';
	else
		cout << "The vector is empty\n";
}