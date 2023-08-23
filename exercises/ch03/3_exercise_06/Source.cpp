#include "..\std_lib_facilities.h"

int main()
{
	int x1, x2, x3;
	cout << "Enter three numbers: ";
	cin >> x1 >> x2 >> x3;

	int temp;
	if (x1 > x2) {
		temp = x2;
		x2 = x1;
		x1 = temp;
	}
	if (x2 > x3) {
		temp = x3;
		x3 = x2;
		x2 = temp;
	}
	if (x1 > x2) {
		temp = x2;
		x2 = x1;
		x1 = temp;
	}

	cout << x1 << ", " << x2 << ", " << x3 << "\n";

	return 0;
}