#include "..\std_lib_facilities.h"

int main()
try
{
	int n;
	cout << "Enter number: ";
	cin >> n;
	if (!cin)
		error("invalid input");

	vector<int> fibs;
	cout << n << " values of the Fibonacci series:\n";
	if (n == 1) {
		fibs.push_back(1);
		cout << fibs[fibs.size() - 1] << "(" << fibs.size() << ") ";
	}
	else if (n >= 2) {
		for (int i = 0; i < n; i++) {
			if (i >= 2)
			{
				int v = narrow_cast<int>(double(fibs[i - 2]) + fibs[i - 1]);
				fibs.push_back(v);
			}
			else
				fibs.push_back(1);
			cout << fibs[i] << "(" << i + 1 << ") ";
		}
	}

	cout << "\n";
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