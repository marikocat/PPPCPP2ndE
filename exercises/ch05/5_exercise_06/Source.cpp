#include "../std_lib_facilities.h"

double ctok(double c) // converts Celsius to Kelvin
{
	if (c < -273.15)
		error("below absolute zero");

	double k = c + 273.15;
	return k;
}

double ctof(double c)
{
	if (c < -273.15)
		error("temperature in C below absolute zero");

	double f = 9.0 / 5 * c + 32;
	return f;
}

double ktoc(double k)
{
	if (k < 0)
		error("below absolute zero");

	double c = k - 273.15;
	return c;
}

double ftoc(double f)
{
	if (f < -459.67)
		error("temperature in F below absolute zero");
	double c = (f - 32) * 5 / 9;
	return c;
}

int main()
try
{
	double c = 0; // declare input variable
	cout << "Enter temperature in C: ";
	cin >> c; // retrieve temperature to input variable

	double f = ctof(c); // convert temperature
	cout << f << "F\n"; // print out temperature

	cout << "Enter temperature in F: ";
	cin >> f;

	c = ftoc(f);
	cout << c << '\n';
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