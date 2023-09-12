#include <iostream>
#include <vector>
using namespace std;

int main()
{
	vector<int> primes;
	int max;
	cout << "Enter max number: ";
	cin >> max;

	vector<bool> is_primes(max + 1, true);
	for (int i = 0; i < 2; i++)
		is_primes[i] = false;
	for (int i = 2; i <= max; i++)
	{
		if (is_primes[i])
			for (int j = i * 2; j <= max; j += i)
				is_primes[j] = false;
	}

	for (int i = 0; i <= max; i++)
		if (is_primes[i] == true)
			primes.push_back(i);

	cout << "{ ";
	for (int p : primes)
		cout << p << " ";
	cout << "}\n";
}