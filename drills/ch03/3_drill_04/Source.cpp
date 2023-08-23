#include <iostream>

using namespace std;

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

	// Output of the letter
	cout << "Dear " << first_name << ",\n"
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
}