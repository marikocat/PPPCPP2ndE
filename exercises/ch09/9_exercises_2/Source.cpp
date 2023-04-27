#include "..\std_lib_facilities.h"

class Name_pairs {
	vector<string> name;
	vector<double> age;
	bool name_exist(const string& s);
	int name_index(const string& s);
public:
	void read_names();
	void read_ages();
	void print();
	
	void sort();
};

bool Name_pairs::name_exist(const string& s)
{
	for (string n : name)
		if (n == s) return true;
	return false;
}

void Name_pairs::read_names()
{
	string n;
	cout << "Enter names (enter 'stop' to quit):\n";
	while (cin >> n && n != "stop") {
		if (!name_exist(n))
			name.push_back(n);
		else
			cout << n << " is already in the list\n";
	}
}

void Name_pairs::read_ages()
{
	double a;
	cout << "Age of:\n";
	for (string n : name) {
		cout << n << " - ";
		cin >> a;
		age.push_back(a);
	}
}

int Name_pairs::name_index(const string& s)
{
	int limit = name.size();
	for (int i = 0; i < limit; i++)
		if (name[i] == s) return i;
	error("No such name found");
}

void Name_pairs::sort()
{
	if (name.size() != age.size()) error("Different sizes");

	vector<string> sortedName{ name };
	std::sort(sortedName.begin(), sortedName.end());
	vector<double> sortedAge{ age };

	int limit = name.size();
	for (int i = 0; i < limit; i++)
	{
		sortedAge[i] = age[name_index(name[i])];
	}

	name = sortedName;
	age = sortedAge;
}

void Name_pairs::print()
{
	cout << "\nPairs:\n";
	int limit = name.size();
	for (int i = 0; i < limit; i++) {
		cout << name[i] << " " << age[i] << "\n";
	}
}

int main()
{
	Name_pairs np;
	np.read_names();
	np.read_ages();
	np.sort();
	np.print();
}