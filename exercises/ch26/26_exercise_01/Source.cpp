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
		if (*middle == val)
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

struct Test
{
	string label;
	int val;
	vector<int> seq;
	bool res;
};

istream& operator>>(istream& is, Test& t)
{
	string a, b;

	if (is >> a >> t.label >> t.val >> b && (a != "{" || b != "{"))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}

	t.seq.clear();
	copy(istream_iterator<int>{is},
		istream_iterator<int>{},
		back_inserter(t.seq));

	is.clear();

	string c, d;

	if (is >> c >> t.res >> d && (c != "}" || d != "}"))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}

	return is;
}

int test_all(istream& is)
{
	int error_count = 0;
	for (Test t; is >> t;)
	{
		bool r = binary_search(t.seq.begin(), t.seq.end(), t.val);
		if (r != t.res)
		{
			cout << "failure: test " << t.label
				<< " binary_search: "
				<< t.seq.size() << " elements, val==" << t.val
				<< " -> " << t.res << '\n';
			++error_count;
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
		int errors = test_all(ifs);
		cout << "number of errors: " << errors << '\n';
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