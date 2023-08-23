#include <iostream>

using namespace std;

int main()
{
	cout << "Enter the name of the person you want to write to:\n";
	string first_name; // first_name is a variable of type string
	cin >> first_name; // read characters into first_name
	cout << "Dear " << first_name << ",\n";
}