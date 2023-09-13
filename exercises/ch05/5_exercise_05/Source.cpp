#include "../std_lib_facilities.h"

double ctok(double c) // converts Celsius to Kelvin
{
	if (c < -273.15)
		error("below absolute zero");

	double k = c + 273.15;
	return k;
}

double ktoc(double k)
{
	if (k < 0)
		error("below absolute zero");

	double c = k - 273.15;
	return c;
}

int main()
try
{
	double c = 0; // declare input variable
	cin >> c; // retrieve temperature to input variable

	double k = ctok(c); // convert temperature
	cout << k << '\n'; // print out temperature

	double kk = 0;
	cin >> kk;

	double cc = ktoc(kk);
	cout << cc << '\n';
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