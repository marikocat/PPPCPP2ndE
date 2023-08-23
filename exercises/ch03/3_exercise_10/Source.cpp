#include "..\std_lib_facilities.h"

int main()
{
	string operation;
	double d1, d2;

	cout << "Enter an operation and operands: ";
	cin >> operation >> d1 >> d2;

	if (operation == "+")
		cout << d1 + d2 << "\n";
	if (operation == "-")
		cout << d1 - d2 << "\n";
	if (operation == "*")
		cout << d1 * d2 << "\n";
	if (operation == "/")
		cout << d1 / d2 << "\n";

	return 0;
}