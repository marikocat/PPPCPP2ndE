#include "../std_lib_facilities.h"

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
		vector<char> letters;
		letters.clear();
		for (int i = 0; i < 4; i++)
		{
			char n;
			while (true)
			{
				n = 65 + rand() % 26;
				int count = 0;
				for (int j = 0; j < letters.size(); j++)
					if (letters[j] == n) count++;
				if (!count) break;
			}
			letters.push_back(n);
			// cout << letters[i] << ' ';
		}
		
		vector<char> userLetters;
		while (true)
		{
			cout << "Enter 4 different nums: ";
			userLetters.clear();
			for (int i = 0; i < 4; i++) {
				char x;
				cin >> x;
				if (!cin)
					error("invalid input");

				for (int j = 0; j < userLetters.size(); j++) {
					if (userLetters[j] == x)
						error("numbers must be different");
				}
				userLetters.push_back(x);
			}

			int bulls = 0;
			int cows = 0;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					if (i == j && userLetters[i] == letters[j]) bulls++;
					else if (userLetters[i] == letters[j]) cows++;
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