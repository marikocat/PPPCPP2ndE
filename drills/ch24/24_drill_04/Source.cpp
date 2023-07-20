#include <iostream>
#include <cmath>
#include <cerrno>
#include <stdexcept>
using namespace std;

int main()
{
	int n;
	while (cin >> n)
	{
		errno = 0;
		double d = sqrt(n);
		if (errno) cerr << "something went wrong with something somewhere\n";
		if (errno == EDOM) // domain error
			cerr << "sqrt() not defined for negative argument\n";
		else
			cout << "Square root of " << n << " is " << d << '\n';
	}
	if (!cin && !cin.eof()) throw exception("bad input");
}