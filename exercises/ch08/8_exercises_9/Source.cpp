#include "..\std_lib_facilities.h"

double compute_index(const vector<double>& price, const vector<double>& weight)
{
	if (price.size() != weight.size())
		error("vectors must be of the same size");
	double result = 0;
	int limit = price.size();
	for (int i = 0; i < limit; i++) {
		result += price[i] * weight[i];
	}
	return result;
}

int main()
{
	vector<double> price = { 10.0, 15.0, 25.0 };
	vector<double> weight = { 1.5, 2.5, 3.5 };
	cout << compute_index(price, weight);
}