#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

int rand_int(int max) { return rand() % max; }
int rand_int(int min, int max) { return min + rand_int(max - min); }
double rand_double(double min, double max)
{
	double k = static_cast<double>(std::rand()) / RAND_MAX; // [0,1]
	return min + k * (max - min);
}

int main()
{
	for (int n = 5000; n < 5000001; n *= 10)
	{
		vector<double> vd;
		for (int i = 0; i < n; i++)
		{
			vd.push_back(rand_double(-10, 10));
		}

		auto start = chrono::system_clock::now();
		sort(vd.begin(), vd.end());
		auto end = chrono::system_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "To sort " << n << " elements of vector<double> took "
			<< duration.count() << " milliseconds\n";
	}
}