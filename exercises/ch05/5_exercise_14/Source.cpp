#include "../std_lib_facilities.h"

int main()
{
	vector<int> monday;
	vector<int> tuesday;
	vector<int> wednesday;
	vector<int> thursday;
	vector<int> friday;
	vector<int> saturday;
	vector<int> sunday;

	int rejected = 0;

	string day;
	int value;

	cout << "Enter day value pairs:\n";
	while (cin >> day >> value)
	{
		if (day == "Monday" || day == "Mon" || day == "monday")
			monday.push_back(value);
		else if (day == "Tuesday" || day == "Tue" || day == "tuesday")
			tuesday.push_back(value);
		else if (day == "Wednesday" || day == "Wed" || day == "wednesday")
			wednesday.push_back(value);
		else if (day == "Thursday" || day == "Thu" || day == "thursday")
			thursday.push_back(value);
		else if (day == "Friday" || day == "Fri" || day == "friday")
			friday.push_back(value);
		else if (day == "Saturday" || day == "Sat" || day == "saturday")
			saturday.push_back(value);
		else if (day == "Sunday" || day == "Sun" || day == "sunday")
			sunday.push_back(value);
		else if ((day == "NoDay" || day == "noday") && value == 0)
			break;
		else
			rejected++;
	}

	int sum = 0;
	cout << "Monday: ";
	for (int i : monday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Tuesday: ";
	for (int i : tuesday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Wednesday: ";
	for (int i : wednesday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Thursday: ";
	for (int i : thursday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Friday: ";
	for (int i : friday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Saturday: ";
	for (int i : saturday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	sum = 0;
	cout << "Sunday: ";
	for (int i : sunday)
	{
		cout << i << " ";
		sum += i;
	}
	cout << "\nSum: " << sum << "\n";

	cout << "The number of rejected values: " << rejected << "\n";
}