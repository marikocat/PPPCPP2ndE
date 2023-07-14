#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// accept a pattern and a set of lines from input
// check the pattern and search for lines with that pattern

int main()
{
	regex pattern;

	string pat;
	cout << "enter pattern: ";
	getline(cin, pat);
	string filename;
	cout << "enter filename: ";
	cin >> filename;

	ifstream ifs{ filename };
	if (!ifs) 
	{
		cerr << "cannot open file\n";
		exit(1);
	}

	try
	{
		pattern = pat; // this checks pat
		cout << "pattern: " << pat << '\n';
	}
	catch (bad_exception)
	{
		cout << pat << " is not a valid regular expression\n";
		exit(1);
	}

	int lineno = 0;
	for (string line; getline(ifs, line);)
	{
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pattern))
		{
			cout << "line " << lineno << ": " << line << '\n';
			for (int i = 0; i < matches.size(); ++i)
			{
				cout << "\tmatches[" << i << "]: "
					<< matches[i] << '\n';
			}
		}
		else
			cout << "line " << lineno << ": didn't match\n";
	}
}