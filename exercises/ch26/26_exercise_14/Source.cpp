#include <iostream>
#include <map>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;

int rand_int(int max) { return rand() % max; }
int rand_int(int min, int max) { return min + rand_int(max - min); }

string rand_string()
{
	int l = rand_int(100);
	string s;
	for (int i = 0; i < l; i++)
		s += char(rand_int('A', 'z'));
	return s;
}

int main()
{
	for (int n = 5000; n < 500001; n *= 10)
	{
		vector<string> vs;
		for (int i = 0; i < n; i++)
		{
			vs.push_back(rand_string());
		}

		auto start = chrono::system_clock::now();
		sort(vs.begin(), vs.end());
		auto end = chrono::system_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "To sort " << n << " elements of vector<string> took "
			<< duration.count() << " milliseconds\n";
	}
	cout << endl;

	for (int n = 5000; n < 500001; n *= 10)
	{
		vector<string> vs;
		for (int i = 0; i < n; i++)
		{
			vs.push_back(rand_string());
		}

		map<string, int> ms;

		auto start = chrono::system_clock::now();
		for (string s : vs)
			ms.insert({ s, s.length() });
		auto end = chrono::system_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "To insert " << n << " elements to map<string, int> took "
			<< duration.count() << " milliseconds\n";
	}
}