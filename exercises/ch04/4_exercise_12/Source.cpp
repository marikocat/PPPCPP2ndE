#include "..\std_lib_facilities.h"

vector<int> primeNums = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97 };

bool is_prime(int x)
{

	for (int i = 0; i < primeNums.size(); i++)
	{
		if (x > primeNums[i])
		{
			if (x % primeNums[i] == 0)
				return false;
		}
		else
		{
			if (x == 1)
				return false;
			return true;
		}
	}
}

int main()
{
	vector<int> primes;
	int max;
	cout << "Enter max number: ";
	cin >> max;

	for (int i = 1; i <= max; i++) {
		if (is_prime(i))
			primes.push_back(i);
	}
	cout << "{ ";
	for (int p : primes)
		cout << p << " ";
	cout << "};\n";
}