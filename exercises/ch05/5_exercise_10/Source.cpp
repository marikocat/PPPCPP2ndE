#include "../std_lib_facilities.h"

int main()
try
{
	vector<double> values;
	int n;
	cout << "Please enter the number of values you want to sum: ";
	cin >> n;
	if (!cin)
		error("invalid input for the number of values to sum");

	cout << "Please enter some floating-point numbers (press '|' to stop): ";
	for (double v; cin >> v;)
		values.push_back(v);

	if (n > values.size())
		error("the number of values to sum is greater than there are in the vector");

	vector<double> differences;
	for (int i = 1; i < values.size(); i++)
		differences.push_back(values[i] - values[i - 1]);

	cout << "The sum of the first " << n << " numbers ( ";
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += values[i];
		cout << values[i] << ' ';
	}
	cout << ") is " << sum << ".\n";

	cout << "Differences: ";
	for (double d : differences)
		cout << d << ' ';
	cout << '\n';
}
catch (runtime_error& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}