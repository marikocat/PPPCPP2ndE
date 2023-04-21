#include "..\std_lib_facilities.h"

int fac(int n) { return n > 1 ? n * fac(n - 1) : 1; }

int main()
{
	for (int i = 0; i <= 20; ++i)
		cout << "Factorial of " << i << " = " << fac(i) << "\n";
}