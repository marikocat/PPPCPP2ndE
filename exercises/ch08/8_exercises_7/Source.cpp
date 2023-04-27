#include "..\std_lib_facilities.h"

const int name_no{ 5 };

void get_names(vector<string>& name)
{
	string n;
	cout << "Enter " << name_no << " names\n";
	for (int i = 0; i < name_no; i++)
	{
		cout << ": ";
		cin >> n;
		name.push_back(n);
	}
}

void get_ages(const vector<string>& name, vector<double>& age)
{
	double a;
	for (string n : name)
	{
		cout << "Enter age for " << n << ": ";
		while (!(cin >> a)) {
			cout << "Sorry, I don't understand you! How old is " << n << "?: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		age.push_back(a);
	}
}

void print_pairs(const vector<string>& name, const vector<double>& age)
{
	int pairs_num = name.size();
	for (int i = 0; i < pairs_num; i++)
	{
		cout << "(" << name[i] << "," << age[i] << ")\n";
	}
}

int name_index(const vector<string>& name, const string& n)
{
	int names_num = name.size();
	for (int i = 0; i < names_num; i++)
		if (name[i] == n) return i;
	error("No element found!");
}

void sort_pairs(vector<string>& name, vector<double>& age)
{
	vector<string> orig_name{ name };
	vector<double> orig_age{ age };

	sort(name.begin(), name.end());
	int names_num = name.size();
	for (int i = 0; i < names_num; i++)
		age[i] = orig_age[name_index(orig_name, name[i])];
}

int main()
{
	try {
		vector<string> name;
		vector<double> age;

		get_names(name);
		get_ages(name, age);
		print_pairs(name, age);
		cout << "\n";
		sort_pairs(name, age);
		print_pairs(name, age);
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}
	catch (...)
	{
		cerr << "Unknown exception!\n";
		return 2;
	}
}