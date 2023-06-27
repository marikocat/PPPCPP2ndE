#include <iostream>
#include <map>
#include <set>
using namespace std;

struct Compare_second {
	bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) const
	{
		return (p1.second == p2.second) ? p1.first < p2.first : p1.second < p2.second;
	}
};

int main()
{
	map<string, int> words;

	for (string s; cin >> s;)
		++words[s];

	for (const auto& p : words)
		cout << p.second << ": " << p.first << '\n';
	cout << '\n';

	set<pair<string, int>, Compare_second> sp{ words.begin(), words.end() };
	for (auto p : sp)
		cout << p.second << ": " << p.first << '\n';
}