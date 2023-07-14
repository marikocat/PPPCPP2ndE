#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	ifstream in{ "file.txt" };
	if (!in)
	{
		cerr << "no file\n";
		exit(1);
	}

	ofstream out{ "out.txt" };
	if (!out)
	{
		cerr << "cannot open file\n";
		exit(1);
	}

	regex pat{ R"(\d{2}[./]\d{2}[./]\d{4})" };

	int lineno = 0;
	for (string line; getline(in, line);)
	{
		++lineno;
		smatch matches;
		if (regex_search(line, matches, pat))
		{
			cout << lineno << ": " << line << '\n';

			int month, day, year;
			char ch1, ch2;
			istringstream iss{ matches[0] };
			iss >> month >> ch1 >> day >> ch2 >> year;
			ostringstream oss;
			oss << year << '-' << month << '-' << day;

			const int from = matches.position(0);
			line.erase(from, matches[0].length());
			line.insert(from, oss.str());
			out << line << '\n';
		}
	}
}