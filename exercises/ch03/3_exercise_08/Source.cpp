#include "..\std_lib_facilities.h"

int main()
{
	cout << "Enter number: ";
	int num;

	while (cin >> num) {
		cout << "The value " << num << " an " << (num % 2 == 0 ? "even" : "odd") << " number.\n";
		cout << "Enter number: ";
	}

	return 0;
}