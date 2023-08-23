#include "../std_lib_facilities.h"

int main()
{
	cout << "Enter the name of the person you want to write to:\n";
	string first_name; // first_name is a variable of type string
	cin >> first_name; // read characters into first_name

	cout << "Enter a friend name:\n";
	string friend_name;
	cin >> friend_name;

	char friend_sex = 0;
	cout << "Enter sex of a friend (f/m):\n";
	cin >> friend_sex;

	int age;
	cout << "Enter the age of the recipient:\n";
	cin >> age;
	if (age < 0 || age > 110)
		simple_error("you're kidding!");

	// Output of the letter
	cout << "\nDear " << first_name << ",\n"
		<< "\tHow are you? I am fine. I miss you.\n"
		<< "Have you seen " << friend_name << " lately?\n";
	if (friend_sex == 'm')
	{
		cout << "If you see " << friend_name << " please ask him to call me.\n";
	}

	if (friend_sex == 'f')
	{
		cout << "If you see " << friend_name << " please ask her to call me.\n";
	}

	cout << "I hear you just had a birthday and you are " << age << " years old.\n";

	if (age < 12)
	{
		cout << "Next year you will be " << age + 1 << ".\n";
	}
	else if (age == 17)
	{
		cout << "Next year you will be able to vote.\n";
	}
	else if (age > 70)
	{
		cout << "I hope you are enjoying retirement.\n";
	}

	cout << "Yours sincerely,\n\nMarina.\n";
}