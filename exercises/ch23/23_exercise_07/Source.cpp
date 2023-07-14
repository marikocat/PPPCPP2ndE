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

	regex pat{ R"( 3[47]\d{13} | 5[1-5]\d{14} | 4\d{12} | 4\d{15} )" };

	int lineno = 0;
	for (string line; getline(in, line);)
	{
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pat))
			cout << lineno << ": " << line << '\n';
	}
}