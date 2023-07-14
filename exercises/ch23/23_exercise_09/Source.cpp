#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct bad_from_string : bad_cast
{
	const char* what() const override
	{
		return "bad cast from string";
	}
};

template<typename T>
T from_string(const string& s)
{
	istringstream is{ s };
	T t;
	if (!(is >> t)) throw bad_from_string{};
	return t;
}

int main()
{
	ifstream in{ "table.txt" };
	if (!in) {
		cerr << "no input file\n";
		exit(1);
	}

	string line;
	int lineno = 0;

	regex header{ R"(^[\w ]+(	[\w ]+)*$)" };
	regex row("^([\\w ]+)(	\\d+)(	\\d+)(	\\d+)$");

	if (getline(in, line))
	{
		smatch matches;
		if (!regex_match(line, matches, header))
			cerr << "no header\n";
	}

	// column totals:
	int boys = 0;
	int girls = 0;

	while (getline(in, line))
	{
		++lineno;
		smatch matches;
		if (!regex_match(line, matches, row))
		{
			cerr << "bad line: " << lineno << '\n';
		}

		// check row
		int curr_boys = from_string<int>(matches[2]);
		int curr_girls = from_string<int>(matches[3]);
		int curr_total = from_string<int>(matches[4]);
		if (curr_boys + curr_girls != curr_total) cerr << "bad row sum\n";

		if ((in >> ws).eof())
		{
			cout << "at the end of the file\n";
			if (curr_boys != boys) cerr << "boys don't add up\n";
			else cout << "boys add up\n";
			if (curr_girls != girls) cerr << "girls don't add u\n";
			else cout << "girls add up\n";
			return 0;
		}

		// update totals
		boys += curr_boys;
		girls += curr_girls;
	}
}