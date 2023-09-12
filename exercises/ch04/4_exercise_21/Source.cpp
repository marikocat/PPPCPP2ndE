#include <iostream>
#include <vector>

using namespace std;

bool is_unique(string n, const vector<string>& names)
{
	for (string s : names)
		if (s == n) return false;
	return true;
}

int find_index(string n, const vector<string>& names)
{
	int index = -1;
	for (int i = 0; i < names.size(); i++)
	{
		if (n == names[i])
		{
			index = i;
			break;
		}
	}
	return index;
}

int main()
try
{
	vector<string> names;
	vector<int> scores;

	string name;
	int score;
	while (cin >> name >> score)
	{
		if (name == "NoName" && score == 0)
			break;

		if (is_unique(name, names))
		{
			names.push_back(name);
			scores.push_back(score);
		}
		else
			throw exception("The name is entered twice\n");
	}

	for (int i = 0; i < names.size(); i++)
	{
		cout << names[i] << ' ' << scores[i] << '\n';
	}

	cout << "Enter a score: ";
	cin.clear();
	cin >> score;
	int count = 0;
	for (int i = 0; i < scores.size(); i++)
	{
		if (score == scores[i])
		{
			cout << names[i] << "\n";
			count++;
		}
	}

	if (count == 0)
		cout << "score not found\n";
	else
		cout << "with the score of " << score << "\n";
}
catch (exception& e)
{
	cerr << e.what();
}
catch (...)
{
	cerr << "unknown error\n";
}