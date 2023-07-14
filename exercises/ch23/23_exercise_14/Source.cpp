#include <regex>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	regex pattern;

	string pat;
	cout << "enter pattern: ";
	getline(cin, pat);

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

	ifstream ifs{ "in.txt" };
	if (!ifs) throw exception("cannot open file");
	int lineno = 0;

	string content;
	for (string line; getline(ifs, line);)
		content += line + '\n';

	smatch matches;
	if (regex_search(content, matches, pattern))
	{
		for (int i = 0; i < matches.size(); ++i)
		{
			cout << "\tmatches[" << i << "]: "
				<< matches[i] << '\n';
		}
	}
	else
		cout << "didn't match\n";
}