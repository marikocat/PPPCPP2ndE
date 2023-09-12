#include <iostream>

using namespace std;

int main()
{
	double d1, d2;
	char op;
	while (cin >> d1 >> d2 >> op)
	{
		if (op == '+')
			cout << "The sum of " << d1 << " and " << d2 << " is " << d1 + d2 << '\n';
		else if (op == '-')
			cout << "The difference of " << d1 << " and " << d2 << " is " << d1 - d2 << '\n';
		else if (op == '*')
			cout << "The product of " << d1 << " and " << d2 << " is " << d1 * d2 << '\n';
		else if (op == '/')
			cout << "The quotient of " << d1 << " and " << d2 << " is " << d1 / d2 << '\n';
		else
			cout << "Unknown operation\n";
	}
}