#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename Iter, typename T>
bool binary_search(Iter first, Iter last, const T& val)
{
	Iter start = first;
	Iter end = last;
	while (start < end)
	{
		Iter middle = start;
		advance(middle, distance(start, end) / 2);
		if (val == *middle)
		{
			return true;
		}
		else if (val < *middle)
		{
			end = middle;
		}
		else
		{
			start = middle;
			if (distance(start, end) == 1)
				return false;
		}
	}
	return false;
}

template<typename T>
struct Test_data
{
	string label;
	T val;
	bool res;
};

template<typename T>
struct Test
{
	vector<T> seq;
	vector<Test_data<T>> tests;
};

template<typename T>
istream& operator>>(istream& is, Test_data<T>& td)
{
	if (!(is >> td.label >> td.val >> td.res))
	{
		cerr << "ERROR: Invalid format for test data" << '\n';
		return is;
	}

	return is;
}

template<typename T>
istream& operator>>(istream& is, Test<T>& t)
{
	string a, b;

	if (is >> a >> b && (a != "{" || b != "{"))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}
	if (!is) return is;

	t.seq.clear();
	copy(istream_iterator<T>{is},
		istream_iterator<T>{},
		back_inserter(t.seq));
	is.clear();

	string c, d;
	if (is >> c && c != "}")
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}
	t.tests.clear();
	for (Test_data<T> td; is >> td;)
	{
		t.tests.push_back(td);
		is >> d;
		if (d == "}") break;
	}

	return is;
}

template<typename T>
int test_all(istream& is)
{
	int error_count = 0;
	int n = 0;
	for (Test<T> t; is >> t;)
	{
		for (int i = 0; i < t.tests.size(); i++)
		{
			bool r = binary_search(t.seq.begin(), t.seq.end(), t.tests[i].val);
			if (r != t.tests[i].res)
			{
				cout << "failure: test " << t.tests[i].label
					<< " binary_search: "
					<< t.seq.size() << " elements, val==" << t.tests[i].val
					<< " -> " << t.tests[i].res << '\n';
				++error_count;
			}
		}
	}
	return error_count;
}

int main()
{
	try
	{
		ifstream ifs("in.txt");
		if (!ifs) throw exception("cannot open input file");

		int errors = test_all<int>(ifs);
		cout << "number of errors: " << errors << '\n';

		vector<int> v{ 0, 1, 1, 1, 1 };
		if (binary_search(v.begin(), v.end(), 0)) cout << "found\n";
		else cout << "not found\n";
	}
	catch (const exception& e)
	{
		cerr << e.what() << '\n';
		exit(1);
	}
	catch (...)
	{
		cerr << "unknown exception\n";
		exit(2);
	}
}