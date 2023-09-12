#include <iostream>

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
	string s;
	double min_m = 0, max_m = 0;
	int num = 0;
	while (cin >> d >> s)
	{
		double d_m = to_meters(d, s);
		if (s != "m")
			cout << d << s << " == ";
		if (num == 0)
		{
			min_m = d_m;
			max_m = d_m;
			cout << d_m << "m\n";
		}
		else
		{
			if (d_m < min_m)
			{
				min_m = d_m;
				cout << d_m << "m the smallest so far\n";
			}
			else if (d_m > max_m)
			{
				max_m = d_m;
				cout << d_m << "m the largest so far\n";
			}
			else
			{
				cout << d_m << "m\n";
			}
		}
		num++;
	}
}