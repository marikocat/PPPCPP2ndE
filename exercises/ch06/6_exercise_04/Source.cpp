#include <iostream>
#include <vector>

using namespace std;

class Name_value
{
public:
	string name;
	int value;
	Name_value(string n, int v) : name(n), value(v) {}
};

bool is_unique(string n, const vector<Name_value>& nvs)
{
	for (Name_value nv : nvs)
		if (nv.name == n) return false;
	return true;
}

int main()
try
{
	vector<Name_value> nvs;

	string name;
	int score;
	while (cin >> name >> score)
	{
		if (name == "NoName" && score == 0)
			break;

		if (is_unique(name, nvs))
		{
			nvs.push_back(Name_value(name, score));
		}
		else
			throw exception("The name is entered twice");
	}

	for (int i = 0; i < nvs.size(); i++)
	{
		cout << nvs[i].name << ' ' << nvs[i].value << '\n';
	}
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}