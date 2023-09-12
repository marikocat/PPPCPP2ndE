#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double to_meters(double l, string unit)
{
	if (unit == "cm")
		return l / 100.0;
	else if (unit == "in")
		return l * 2.54 / 100.0;
	else if (unit == "ft")
		return l * 12 * 2.54 / 100.0;
	else
		return l;
}

int main()
{
	double d;
	string u;
	string min_u = "m", max_u = "m";
	double min = 0, max = 0;
	double min_m = 0, max_m = 0, sum_m = 0;
	vector<double> values;
	int num = 0;
	while (cin >> d >> u)
	{
		if (u == "m" || u == "cm" || u == "in" || u == "ft")
		{
			double d_m = to_meters(d, u);
			values.push_back(d_m);
			sum_m += d_m;

			if (u != "m")
				cout << d << u << " == ";

			if (num == 0)
			{
				min_m = d_m;
				max_m = d_m;
				min = d;
				max = d;
				min_u = u;
				max_u = u;
				cout << d_m << "m\n";
			}
			else
			{
				if (d_m < min_m)
				{
					min_m = d_m;
					min = d;
					min_u = u;
					cout << d_m << "m the smallest so far\n";
				}
				else if (d_m > max_m)
				{
					max_m = d_m;
					max = d;
					max_u = u;
					cout << d_m << "m the largest so far\n";
				}
				else
				{
					cout << d_m << "m\n";
				}
			}
			num++;
		}
		else
		{
			cout << "Sorry, I don't know a unit called " << u << '\n';
		}
	}

	cout << min << min_u << " == " << min_m << "m the smallest so far\n";
	cout << max << max_u << " == " << max_m << "m the largest so far\n";
	cout << "the sum is " << sum_m << "m\n";
	cout << "the number of values is " << num << '\n';

	sort(values.begin(), values.end());
	for (double v : values)
		cout << v << "m\n";
}