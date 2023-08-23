#include "..\std_lib_facilities.h"

int main()
{
	string input;
	cout << "Enter spelled-out number: ";
	cin >> input;

	int n;
	if (input == "zero")
		n = 0;
	else if (input == "one")
		n = 1;
	else if (input == "two")
		n = 2;
	else if (input == "three")
		n = 3;
	else if (input == "four")
		n = 4;
	else
	{
		cout << "not a number I know\n";
		return 1;
	}

	cout << n << "\n";
	return 0;
}