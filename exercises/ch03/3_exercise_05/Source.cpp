#include "..\std_lib_facilities.h"

int main()
{
	double val1, val2;
	cout << "Enter first number: ";
	cin >> val1;
	cout << "Enter second number: ";
	cin >> val2;
	if (val1 > val2)
		cout << "First num is bigger.\n";
	else if (val1 < val2)
		cout << "First num is smaller.\n";
	else
		cout << "Numbers are equal.\n";
	cout << "Sum = " << val1 + val2 << "\n";
	cout << "Difference = " << val1 - val2 << "\n";
	cout << "Product = " << val1 * val2 << "\n";
	cout << "Ratio = " << val1 / val2 << "\n";

	return 0;
}