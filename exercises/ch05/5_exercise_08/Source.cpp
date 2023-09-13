#include "../std_lib_facilities.h"

int main()
try
{
	vector<int> values;
	int n;
	cout << "Please enter the number of values you want to sum: ";
	cin >> n;
	if (!cin)
		error("invalid input for the number of values to sum");
	
	cout << "Please enter some integers (press '|' to stop): ";
	for (int v; cin >> v;)
		values.push_back(v);

	if (n > values.size())
		error("the number of values to sum is greater than there are in the vector");

	

	cout << "The sum of the first " << n << " numbers ( ";
	int sum = 0;
	for (int i = 0; i < n; i++)
	{
		sum += values[i];
		cout << values[i] << ' ';
	}
	cout << ") is " << sum << ".\n";
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