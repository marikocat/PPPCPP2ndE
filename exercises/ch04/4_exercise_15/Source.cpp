#include "..\std_lib_facilities.h"

int main()
{
	vector<int> primes;
	int n;
	cout << "Enter number of primes: ";
	cin >> n;

	for (int count = 0, i = 2, j; count < n; i++)
	{
		for (j = 2; j < i; j++)
		{
			if (i % j == 0)
				break;
		}

		if (i == j) {
			primes.push_back(i);
			count++;
		}
	}

	cout << "{ ";
	for (int p : primes)
		cout << p << " ";
	cout << "}\n";
}