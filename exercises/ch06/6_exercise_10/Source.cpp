#include "../std_lib_facilities.h"

int calc_permutations(int a, int b);
int calc_combinations(int a, int b);
int factorial(int x);

int main()
try
{
	int a, b;
	cout << "Enter two numbers: ";
	if (!(cin >> a >> b)) error("invalid input");

	cout << "Do you want to calculate permutations or combinations (p/c): ";
	char c;
	if (!(cin >> c)) error("invalid input");

	switch (c) {
	case 'p':
		cout << "P(" << a << ',' << b << ") = " << calc_permutations(a, b) << '\n';
		break;
	case 'c':
		cout << "C(" << a << ',' << b << ") = " << calc_combinations(a, b) << '\n';
		break;
	default:
		error("bad input instruction");
	}

	return 0;
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}

int factorial(int x)
{
	if (x < 0) error("factorial not defined for negative values");
	if (x > 31) error("factorial defined only for ints (too large)");

	int result = 1;
	for (int i = x; i > 1; i--) {
		result *= i;
	}
	return result;
}

int calc_permutations(int a, int b) {
	if (a < b || a < 1 || b < 1) error("bad permutation sizes");

	return factorial(a) / factorial(a - b);
}

int calc_combinations(int a, int b) {
	return calc_permutations(a, b) / factorial(b);
}