#include "../std_lib_facilities.h"

int main()
try
{
	vector<string> unit{ " ones ", " tens ", " hundred ", " thousand " };
	vector<int> digit;

	cout << "Please enter an integer with no more than " << unit.size()
		<< "\ndigits followed by semicolon and a newline: ";

	char ch;
	while (cin >> ch)
	{
		if (ch < '0' || ch > '9') break;
		digit.push_back(ch - '0');
	}

	if (digit.size() == 0) error("no digits");
	if (digit.size() > unit.size()) error("cannot handle that many digits");

	int num = 0;
	for (int i = 0; i < digit.size(); ++i)
	{
		if (digit[i])
			cout << digit[i] << unit[digit.size() - i - 1];
		num = num * 10 + digit[i];
	}
	cout << "\nthat is " << num << '\n';
}
catch (runtime_error& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}