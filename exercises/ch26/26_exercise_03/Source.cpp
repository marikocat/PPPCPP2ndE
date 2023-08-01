#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

template<typename T>
struct More
{
	bool operator()(T t1, T t2) { return t1 > t2; }
};

template<typename Iter, typename T, typename Comp>
bool binary_search(Iter first, Iter last, const T& val, Comp comp)
{
	Iter start = first;
	Iter end = last;
	while (start < end)
	{
		Iter middle = start;
		advance(middle, distance(start, end) / 2);
		if (comp(val, *middle))
		{
			end = middle;
		}
		else
		{
			if (val == *middle)
			{
				return true;
			}
			else
			{
				start = middle;
				if (distance(start, end) == 1)
					return false;
			}
		}
	}
	return false;
}

template<typename T>
struct Test
{
	string label;
	T val;
	vector<T> seq;
	bool res;
};

template<typename T>
istream& operator>>(istream& is, Test<T>& t)
{
	cout << "here\n";
	string a, b;

	if (is >> a >> t.label >> t.val >> b && (a != "{" || b != "{"))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}
	if (!is) cout << "!is\n";
	t.seq.clear();
	copy(istream_iterator<T>{is},
		istream_iterator<T>{},
		back_inserter(t.seq));

	is.clear();

	string c, d;

	if (is >> c >> t.res >> d && (c != "}" || d != "}"))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}
	cout << "return\n";
	return is;
}

template<typename T>
int test_all(istream& is)
{
	int error_count = 0;
	int i = 0;
	for (Test<T> t; is >> t;)
	{
		cout << ++i << '\n';
		bool r = binary_search(t.seq.begin(), t.seq.end(), t.val, More<T>());
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
		int errors = test_all<int>(ifs);
		cout << "number of errors: " << errors << '\n';

		vector<string> v{ "night", "hi", "hello", "day", "answer" };
		if (binary_search(v.begin(), v.end(), "days", More<string>())) cout << "found\n";
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