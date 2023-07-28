#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;

int rand_int(int max) { return rand() % max; }
int rand_int(int min, int max) { return rand_int(max - min) + min; }

template<typename T>
string to_string(const T& t)
{
	ostringstream os;
	os << t;
	return os.str();
}

ostream& make_test(ostream& os, const string& lab, int n, int base, int spread)
{
	os << "{ " << lab << " ";
	vector<int> v;
	int elem = base;
	for (int i = 0; i < n; i++)
	{
		elem += rand_int(spread);
		v.push_back(elem);
	}

	int val = base + rand_int(elem - base);
	os << val << " { ";

	bool found = false;
	for (int i = 0; i < n; i++)
	{
		if (v[i] == val) found = true;
		os << v[i] << " ";
	}
	os << "} " << found << " }\n";
	return os;
}

ostream& make_test2(ostream& os, const string& lab, int n, int base, int spread)
{
	os << "{ " << lab << " ";
	vector<int> v;
	int elem = base;
	for (int i = 0; i < n; i++)
	{
		elem = rand_int(spread);
		v.push_back(elem);
	}
	sort(v.begin(), v.end());

	int val = rand_int(spread);
	os << val << " { ";

	bool found = false;
	for (int i = 0; i < n; i++)
	{
		if (v[i] == val) found = true;
		os << v[i] << " ";
	}
	os << "} " << found << " }\n";
	return os;
}

int main()
{
	ofstream ofs{ "out.txt", ios::app };
	string lab = "rand_test_";
	make_test(ofs,
		lab + to_string(0),
		rand_int(1000),
		0,
		rand_int(50));
	cout << '\n';

	int no_of_tests = 10;
	for (int i = 1; i < no_of_tests + 1; i++)
	{
		string lab = "rand_test_";
		make_test(ofs,
			lab + to_string(i),
			rand_int(100),
			0,
			rand_int(50));
	}
	cout << '\n';

	for (int i = 11; i < no_of_tests + 11; i++)
	{
		string lab = "rand_test_";
		make_test2(ofs,
			lab + to_string(i),
			rand_int(20),
			0,
			10);
	}
}