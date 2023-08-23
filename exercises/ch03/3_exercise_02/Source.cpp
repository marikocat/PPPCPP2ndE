#include "..\std_lib_facilities.h"

int main()
{
	cout << "Enter miles: ";
	double miles;
	cin >> miles;

	cout << miles << " miles equals " << miles * 1.609 << " kilometers.\n";

	return 0;
}