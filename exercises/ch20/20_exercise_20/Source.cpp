#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

int main()
{
	srand(time(NULL));

	const int n = 10000; // repeat n times
	vector<int> vi;
	auto t1 = chrono::system_clock::now(); // begin time
	for (int i = 0; i < n; i++)
	{
		int k = rand() % n;
		auto p = upper_bound(vi.begin(), vi.end(), k);
		// auto p = vi.begin();
		vi.insert(p, k);
	}
	auto t2 = chrono::system_clock::now(); // end time
	cout << "insertion into vector " << n << " times took "
		<< chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << "milliseconds\n";

	list<int> li;
	auto tl1 = chrono::system_clock::now(); // begin time
	for (int i = 0; i < n; i++)
	{
		int k = rand() % n;
		auto p = upper_bound(li.begin(), li.end(), k);
		// auto p = li.begin();
		li.insert(p, k);
	}
	auto tl2 = chrono::system_clock::now(); // end time
	cout << "insertion into list " << n << " times took "
		<< chrono::duration_cast<chrono::milliseconds>(tl2 - tl1).count() << "milliseconds\n";
}