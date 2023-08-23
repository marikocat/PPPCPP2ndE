#include "..\std_lib_facilities.h"

int main()
{
	int pennies = 0;
	int nickels = 0;
	int dimes = 0;
	int quarters = 0;
	int half_dollars = 0;
	int dollars = 0;
	cout << "How many pennies do you have? ";
	cin >> pennies;
	cout << "How many nickels do you have? ";
	cin >> nickels;
	cout << "How many dimes do you have? ";
	cin >> dimes;
	cout << "How many quarters do you have? ";
	cin >> quarters;
	cout << "How many half-dollars do you have? ";
	cin >> half_dollars;
	cout << "How many dollars do you have? ";
	cin >> dollars;

	cout << "You have " << pennies << " pennie" << (pennies == 1 ? "." : "s.") << "\n";
	cout << "You have " << nickels << " nickel" << (nickels == 1 ? "." : "s.") << "\n";
	cout << "You have " << dimes << " dime" << (dimes == 1 ? "." : "s.") << "\n";
	cout << "You have " << quarters << " quarter" << (quarters == 1 ? "." : "s.") << "\n";
	cout << "You have " << half_dollars << " half dollar" << (half_dollars == 1 ? "." : "s.") << "\n";
	cout << "You have " << dollars << " dollar" << (dollars == 1 ? "." : "s.") << "\n";
	int cents = pennies * 1 + nickels * 5 + dimes * 10 + quarters * 25 + half_dollars * 50 + dollars * 100;
	cout << "The value of all of your coins is " << "$" << cents / 100.0 << " or " << cents << " cents.\n";

	return 0;
}