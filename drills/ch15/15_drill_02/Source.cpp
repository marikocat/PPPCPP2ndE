#include "..\std_lib_facilities.h"

struct Person {
	Person() {}
	Person(string first_name, string second_name, int a);

	string get_first_name() const { return fn; }
	string get_second_name() const { return sn; }
	int get_age() const { return age; }
private:
	string fn;
	string sn;
	int age;
};

Person::Person(string first_name, string second_name, int a) : fn{ first_name }, sn{ second_name }, age{ a }
{
	string bad_chars = ";:\"\'[]*&^%$#@!";
	for (char c : bad_chars)
	{
		if (first_name.find(c) != string::npos) error("invalid first name");
		if (second_name.find(c) != string::npos) error("invalid second name");
	}

	if (age < 0 || age >= 150) error("invalid age");
}

ostream& operator<<(ostream& os, const Person& p)
{
	os << p.get_first_name() << " " << p.get_second_name() << " " << p.get_age();
	return os;
}

istream& operator>>(istream& is, Person& p)
{
	string pfn;
	string psn;
	int pa;
	is >> pfn >> psn >> pa;
	if (!is) return is;

	p = Person{ pfn, psn, pa };
	return is;
}

int main()
try
{
	Person person{ "Goofy", "Goofy", 63 };
	cout << person << "\n";

	vector<Person> people;
	for (Person pp; cin >> pp;)
		people.push_back(pp);

	for (Person& p : people)
		cout << p << "\n";
}
catch (exception& e)
{
	cout << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}