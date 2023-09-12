#include "..\std_lib_facilities.h"

int main()
{
	vector<string> choices = { "paper", "rock", "scissors" };
	char c;
	string us, cs;
	int userCount = 0, compCount = 0;
	int comp, user = 0;
	cout << "Play three rounds\n";
	for (int i = 0; i < 3; i++) {
		cout << "Enter your choice (p/r/s): ";
		cin >> c;
		switch (c) {
		case 'p':
			us = choices[0];
			break;
		case 'r':
			us = choices[1];
			break;
		case 's':
			us = choices[2];
			break;
		}
		cout << "Your choice: " << us << "\n";
		cs = choices[(i + 1) % choices.size()];
		cout << "Computer choice: " << cs << "\n";
		if (us == cs)
		{
			cout << "Tie round.\n";
		}
		else
		{
			if ((us == "scissors" && cs == "paper") ||
				(us == "paper" && cs == "rock") ||
				(us == "rock" && cs == "scissors")) {
				userCount++;
				cout << "Your round.\n";
			}
			else {
				compCount++;
				cout << "Computer's round.\n";
			}
		}
		if (userCount == 2 || compCount == 2) break;
	}

	if (userCount == compCount)
		cout << "It's a tie.\n";
	else if (userCount > compCount)
		cout << "You win.\n";
	else
		cout << "Computer wins.\n";
}