#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<double> temps;
	for (double temp; cin >> temp;)
	{
		temps.push_back(temp);
	}

	// compute mean temperature:
	double sum = 0;
	for (int x : temps) sum += x;
	cout << "Average temperature: " << sum / temps.size() << '\n';

	// compute median temperature:
	sort(temps.begin(), temps.end());
	if (temps.size() % 2 == 0)
	{
		double res = (temps[temps.size() / 2] + temps[temps.size() / 2 - 1]) / 2;
		cout << "Median temperature: " << res << '\n';
	}
	else
		cout << "Median temperature: " << temps[temps.size() / 2] << '\n';
}