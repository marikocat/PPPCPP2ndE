#include <iostream>
#include <fstream>
#include <vector>
using std::cerr;
using std::cout;
using std::copy;
using std::exception;
using std::ifstream;
using std::ios_base;
using std::vector;

double* get_from_jack(int* count)
{
	if (!count) return nullptr;
	const int n = 10;
	double* pa = new double[n];
	if (pa)
	{
		ifstream ifs{ "input1.txt" };
		if (!ifs)
			throw exception("cannot open input1 file");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);

		int i = 0;
		int arr_size = n;
		for (double d; ifs >> d;)
		{
			if (i == arr_size)
			{
				double* p = new double[2 * arr_size];
				copy(pa, pa + arr_size, p);
				delete[] pa;
				pa = p;
				arr_size *= 2;
			}
			pa[i] = d;
			++i;
		}
		if (!ifs && !ifs.eof())
			throw exception("invalid input");
		*count = i;
	}
	return pa;
}

vector<double>* get_from_jill()
{
	vector<double>* v = new vector<double>;

	if (v)
	{
		ifstream ifs{ "input2.txt" };
		if (!ifs)
			throw exception("cannot open input2 file");
		ifs.exceptions(ifs.exceptions() | ios_base::badbit);

		for (double d; ifs >> d;) v->push_back(d);
		if (!ifs && !ifs.eof())
			throw exception("invalid input");
	}
	return v;
}

template<typename Iterator>
Iterator high(Iterator first, Iterator last)
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();
	vector<double>& v = *jill_data;

	auto jack_high = high(jack_data, jack_data + jack_count);
	auto jill_high = high(v.begin(), v.end());

	if (jill_high == v.end()) cout << "No Jill's data\n";
	else cout << "Jill's high " << *jill_high << '\n';
	if (jack_high == jack_data + jack_count) cout << "No Jack's data\n";
	else cout << "Jack's high " << *jack_high << '\n';

	delete[] jack_data;
	delete jill_data;
}

int main()
try
{
	fct();
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}