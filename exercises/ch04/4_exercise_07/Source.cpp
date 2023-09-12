#include "..\std_lib_facilities.h"

void print_sum(int x1, int x2)
{
	cout << "The sum of " << x1 << " and " << x2 << " is " << x1 + x2 << ".\n";
}

void print_diff(int x1, int x2)
{
	cout << "The difference of " << x1 << " and " << x2 << " is " << x1 - x2 << ".\n";
}

void print_prod(int x1, int x2)
{
	cout << "The product of " << x1 << " and " << x2 << " is " << x1 * x2 << ".\n";
}

void print_fract(int x1, int x2)
{
	cout << "The quotient of " << x1 << " and " << x2 << " is " << double(x1) / x2 << ".\n";
}

int main()
{
	vector<string> numbers{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	string in1, in2;
	string op;
	
	cout << "Enter two values and operation (+-*/)\n";
	while (cin >> in1 >> in2 >> op)
	{
		int x1 = -1, x2 = -1;
		for (int i = 0; i < numbers.size(); i++)
		{
			if (numbers[i] == in1)
				x1 = i;
			if (numbers[i] == in2)
				x2 = i;
		}
		if (x1 == -1)
			x1 = stoi(in1);
		if (x2 == -1)
			x2 = stoi(in2);

		if (op == "+")
			print_sum(x1, x2);
		else if (op == "-")
			print_diff(x1, x2);
		else if (op == "*")
			print_prod(x1, x2);
		else if (op == "/")
			print_fract(x1, x2);
		else
			cout << "Unknown operation\n";

		cout << "Enter two values and operation (+-*/)\n";
	}
}