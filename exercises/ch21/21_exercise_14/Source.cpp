#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct Frequency {
	bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) const
	{
		if (p1.second == p2.second) return p1.first < p2.first;
		else return p1.second < p2.second;
	}
};

struct Size {
	bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) const
	{
		if (p1.first.size() == p2.first.size()) return p1.first < p2.first;
		else return p1.first.size() < p2.first.size();
	}
};

int main()
{
	ifstream ifs{ "out.txt" };
	if (!ifs) throw exception("cannot open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<string> buffer;
	map<string, int> msi;
	for (string s; ifs >> s;)
	{
		buffer.push_back(s);
		++msi[s];
	}
	if (!ifs && !ifs.eof()) throw exception("invalid input");

	cout << "How many occurrences of ship are there in a file? ";
	cout << count(buffer.begin(), buffer.end(), "ship") << '\n';

	set<pair<string, int>, Frequency> spsi{ msi.begin(), msi.end() };
	cout << "Which word occurs most frequently? ";
	cout << spsi.rbegin()->first << ": " << spsi.rbegin()->second << " times\n";

	set<pair<string, int>, Size> spsi2{ msi.begin(), msi.end() };
	cout << "Which is the longest word in the file? ";
	cout << spsi2.rbegin()->first << '\n';

	cout << "Which is the shortest ? ";
	cout << spsi2.begin()->first << '\n';

	cout << "List all words starting with s.\n";
	auto p = find_if(msi.begin(), msi.end(),
		[](const pair<string, int>& p) {return p.first.front() == 's'; });
	auto q = find_if(msi.rbegin(), msi.rend(),
		[](const pair<string, int>& p) {return p.first.front() == 's'; });
	do
	{
		cout << p++->first << '\n';
	} while (*p != *q);

	cout << "\nList all four-letter words.\n";
	auto p2 = find_if(spsi2.begin(), spsi2.end(),
		[](const pair<string, int>& p) {return p.first.size() == 4; });
	auto q2 = find_if(spsi2.rbegin(), spsi2.rend(),
		[](const pair<string, int>& p) {return p.first.size() == 4; });
	do
	{
		cout << p2++->first << '\n';
	} while (*p2 != *q2);
}