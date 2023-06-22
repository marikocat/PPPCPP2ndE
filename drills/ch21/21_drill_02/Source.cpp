#include <iostream>
#include <map>
#include <numeric>
using namespace std;

template<typename T1, typename T2>
ostream& operator<<(ostream& os, pair<T1, T2> p)
{
	os << "(\"" << p.first << "\", " << p.second << ")\n";
	return os;
}

void fill_map(map<string, int>& m)
{
	string s;
	int i;
	char ch1, ch2;
	while (cin >> ch1 >> s >> i >> ch2)
	{
		cout << "we are here\n";
		if (ch1 != '(' || ch2 != ')') throw exception("invalid input");
		m[s] = i;
		cout << m[s] << '\n';
	}
	if (!cin && !cin.eof())
		throw exception("cannot read input");
}

int main()
{
	map<string, int> msi;
	msi["lecture"] = 21;
	msi["class"] = 22;
	msi["table"] = 35;
	msi["notepad"] = 50;
	msi["chair"] = 35;
	msi["pen"] = 60;
	msi["calculator"] = 30;
	msi["board"] = 1;
	msi["lamp"] = 2;
	msi["desk"] = 1;

	for (const auto& p : msi)
		cout << p;

	msi.clear();
	for (const auto& p : msi)
		cout << p;
	cout << "\ncleared\n";

	try
	{
		fill_map(msi);
	}
	catch (exception& e)
	{
		cout << e.what() << '\n';
	}
	for (const auto& p : msi)
		cout << p;

	int res = accumulate(msi.begin(), msi.end(), 0,
		[](int i, const pair<string, int>& p) {return i + p.second; });
	cout << res << '\n';

	map<int, string> mis;
	for (const auto& p : msi)
		mis[p.second] = p.first;

	for (const auto& p : mis)
		cout << p;
}