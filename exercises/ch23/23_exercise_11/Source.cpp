#include <regex>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
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

struct Line_nums
{
	int boys;
	int girls;
	int total;

	Line_nums& operator+=(Line_nums arg)
	{
		this->boys += arg.boys;
		this->girls += arg.girls;
		this->total += arg.total;
		return *this;
	}
};

int main()
{
	ifstream in{ "table.txt" };
	if (!in)
	{
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

	map<int, Line_nums> rows;
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

		if (matches[1] == "Alle klasser")
		{
			if (curr_boys != boys) cerr << "boys don't add up\n";
			if (curr_girls != girls) cerr << "girls don't add u\n";
			if (!(in >> ws).eof()) cerr << "character after total line\n";
			cout << "all good\n";
			return 0;
		}

		// update totals
		boys += curr_boys;
		girls += curr_girls;

		int initial_digit;
		istringstream iss{ matches[1] };
		if (isdigit(iss.str().front()))
		{
			iss >> initial_digit;
			rows[initial_digit] += Line_nums{ curr_boys, curr_girls, curr_total };
		}
		else
		{
			int year_total = 0;
			for (const auto& p : rows)
			{
				if (year_total)
				{
					if (year_total > p.second.total) cout << "There are fewer students this current " << p.first << " year than previous year.\n";
					else if (year_total == p.second.total) cout << "There is the same number of students this current " << p.first << " year as previous year.\n";
					else cout << "There are more students this current " << p.first << " year than previous year.\n";
				}
				year_total = p.second.total;
			}
		}
	}

	cerr << "didn't find total line\n";
}