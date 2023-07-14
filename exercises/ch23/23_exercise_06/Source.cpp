#include <iostream>
#include <regex>
#include <string>
#include <fstream>
using namespace std;

int main()
{
	ifstream in{ "file.txt" };
	if (!in)
	{
		cerr << "no file\n";
		exit(1);
	}

	regex pat{ R"(\d{2}[./]\d{2}[./]\d{4})" };

	int lineno = 0;
	for (string line; getline(in, line);)
	{
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pat))
			cout << lineno << ": " << line << '\n';
	}
}