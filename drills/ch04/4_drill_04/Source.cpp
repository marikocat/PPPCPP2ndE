#include <iostream>

using namespace std;

int main()
{
	double x1, x2;
	while (cin >> x1 >> x2)
	{
		if (x1 < x2)
		{
			cout << "the smaller value is: " << x1 << '\n';
			cout << "the larger value is: " << x2 << '\n';
		}
		else if (x1 > x2)
		{
			cout << "the smaller value is: " << x2 << '\n';
			cout << "the larger value is: " << x1 << '\n';
		}
		else
			cout << "the numbers are equal\n";
	}
}