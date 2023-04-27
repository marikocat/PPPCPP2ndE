#include "..\std_lib_facilities.h"

double maxv(const vector<double> v) {
	int limit = v.size();
	double max = v[0];
	for (int i = 1; i < limit; i++) {
		if (max < v[i]) max = v[i];
	}
	return max;
}

int main()
{
	vector<double> v = { 1.5, 7.2, 5.6, 10.8, 9.6 };
	cout << maxv(v);
}