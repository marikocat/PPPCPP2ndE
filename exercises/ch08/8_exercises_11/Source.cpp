#include "..\std_lib_facilities.h"

struct Results {
	double min;
	double max;
	double mean;
	double median;
};

Results my_func(const vector<double> v) {
	Results temp;
	int limit = v.size();
	vector<double> tmp{ v };
	sort(tmp.begin(), tmp.end());
	temp.min = tmp[0];
	temp.max = tmp[limit - 1];
	double sum = 0;
	for (int i = 0; i < limit; i++) {
		sum += tmp[i];
	}
	temp.mean = sum / limit;
	if (limit % 2 == 0) {
		temp.median = (tmp[limit / 2 - 1] + tmp[limit / 2]) / 2;
	}
	else {
		temp.median = tmp[limit / 2];
	}

	return temp;
}

int main()
{
	vector<double> v = { 1, 6, 7, 8, 5, 4, 3, 2 };
	Results res = my_func(v);
	cout << "Min: " << res.min << "\n";
	cout << "Max: " << res.max << "\n";
	cout << "Mean: " << res.mean << "\n";
	cout << "Median: " << res.median << "\n";
}