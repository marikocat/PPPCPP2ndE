#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

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

double* high(double* first, double* last)
{
	double* high = first;
	for (double* p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

void fct()
{
	int jack_count = 0;
	double* jack_data = get_from_jack(&jack_count);
	vector<double>* jill_data = get_from_jill();
	vector<double>& v = *jill_data;

	double* jack_high = high(jack_data, jack_data + jack_count); // jack_high will point to the element with the highest value
	double* jill_high = high(&v[0], &v[0] + v.size()); // jill_high will point to the element with the highest value

	cout << "Jill's max: " << *jill_high
		<< "; Jack's max: " << *jack_high
		<< "\n";

	double* middle = &v[0] + v.size() / 2;
	double* high1 = high(&v[0], middle); // max of first half
	double* high2 = high(middle, &v[0] + v.size()); // max of second half

	cout << "Jill's max in first half: " << *high1 << "\n";
	cout << "Jill's max in second half: " << *high2 << "\n";

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