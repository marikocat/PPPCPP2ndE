#include "..\std_lib_facilities.h"

int main()
try
{
	int seed;
	cout << "Enter any number: ";
	cin >> seed;
	if (!cin)
		error("invalid input");

	srand(seed);

	char play = 'y';
	while (play == 'y')
	{
		vector<int> numbers;
		numbers.clear();
		for (int i = 0, n; i < 4; i++)
		{
			while (true)
			{
				n = rand() % 10;
				int count = 0;
				for (int j = 0; j < numbers.size(); j++)
					if (numbers[j] == n) count++;
				if (!count) break;
			}
			numbers.push_back(n);
		}

		vector<char> userNumbers;
		while (true)
		{
			cout << "Enter 4 different nums: ";
			userNumbers.clear();
			for (int i = 0, x; i < 4; i++) {
				cin >> x;
				if (!cin)
					error("invalid input");

				for (int j = 0; j < userNumbers.size(); j++) {
					if (userNumbers[j] == x)
						error("numbers must be different");
				}
				userNumbers.push_back(x);
			}

			int bulls = 0;
			int cows = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j && userNumbers[i] == numbers[j]) bulls++;
					else if (userNumbers[i] == numbers[j]) cows++;
				}
			}
			cout << bulls << " bulls and " << cows << " cows\n";
			if (bulls == 4) break;
			else cout << "Try again\n";
		}
		cout << "You win! Play again? (y/n): ";
		cin >> play;
		cout << '\n';
	}

	cout << "See you later!\n";
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