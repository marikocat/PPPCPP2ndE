#include "..\std_lib_facilities.h"

void printRoots(double a, double b, double c)
{
	double discr = b * b - 4 * a * c;
	if (discr < 0) {
		error("Discriminant less then zero. No roots.\n");
	}
	else if (discr == 0) {
		double x = -b / (2 * a);
		cout << x << '\n';
	}
	else {
		double x1 = (-b + sqrt(discr)) / (2 * a);
		double x2 = (-b - sqrt(discr)) / (2 * a);
		cout << x1 << ' ' << x2 << '\n';
	}
}

int main()
try
{
	double a, b, c;
	cout << "Enter coefficients: ";
	cin >> a >> b >> c;
	if (!cin)
		error("invalid input");

	printRoots(a, b, c);
}
catch (runtime_error& e) {
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}