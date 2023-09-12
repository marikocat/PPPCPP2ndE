#include "..\std_lib_facilities.h"

int main()
{
	double a, b, c, discriminant, result;
	cout << "Enter a b c values: ";
	cin >> a >> b >> c;

	discriminant = b * b - 4 * a * c;
	if (discriminant > 0) {
		result = (-b + sqrt(discriminant)) / (2 * a);
		cout << "First root: " << result << "\n";
		result = (-b - sqrt(discriminant)) / (2 * a);
		cout << "Second root: " << result << "\n";
	}
	else if (discriminant == 0) {
		result = (-b) / (2 * a);
		cout << "The root is: " << result << "\n";
	}
	else {
		cout << "There is no roots.\n";
	}
}