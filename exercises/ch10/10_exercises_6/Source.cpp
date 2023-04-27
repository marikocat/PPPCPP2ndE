#include "..\std_lib_facilities.h"

const string roman_zero = "nulla";
const vector<char> roman_numerals = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
const vector<int> arabic_numerals = { 1, 5, 10, 50, 100, 500, 1000 };

bool are_valid_numerals(const string& ns);
int get_numeral_index(char numeral);

class Roman_int {
public:
	Roman_int();
	Roman_int(const string& numerals);

	int as_int() const { return i; }
	string numerals() const { return n; }
private:
	string n;
	int i;
};

Roman_int::Roman_int() : n{roman_zero}, i{0} {}

Roman_int::Roman_int(const string& numerals) : n{numerals}
{
	if (!are_valid_numerals(numerals)) error("invalid numerals");

	int result = 0;
	if (numerals == roman_zero) i = result;
	else
	{
		vector<int> numerals_indexes;
		for (char n : numerals)
			numerals_indexes.push_back(get_numeral_index(n));

		for (int i = 0; i < numerals.size(); ++i)
		{
			if (i < numerals.size() - 1 && numerals_indexes[i] < numerals_indexes[i + 1])
			{
				result += arabic_numerals[numerals_indexes[i + 1]] - arabic_numerals[numerals_indexes[i]];
				++i;
			}
			else
				result += arabic_numerals[numerals_indexes[i]];
		}
		i = result;
	}
}

ostream& operator<<(ostream& os, const Roman_int& ri)
{
	os << ri.numerals();
	return os;
}

istream& operator>>(istream& is, Roman_int& ri)
{
	string ns;
	is >> ns;
	if (!is) return is;
	ri = Roman_int{ ns };
	return is;
}

bool are_valid_numerals(const string& ns)
{
	vector<int> numerals_indexes;
	for (char n : ns)
		numerals_indexes.push_back(get_numeral_index(n));
	
	for (int i = 0; i < ns.size(); ++i)
	{
		// numeral can be repeated only thrice
		if (i + 3 < ns.size() &&
			numerals_indexes[i] == numerals_indexes[i + 1] &&
			numerals_indexes[i] == numerals_indexes[i + 2] &&
			numerals_indexes[i] == numerals_indexes[i + 3])
			return false;
		// V, L and D can't precede greater or same numerals
		if (numerals_indexes[i] % 2 != 0 &&
			i + 1 < ns.size() &&
			numerals_indexes[i] <= numerals_indexes[i + 1])
			return false;
		// numeral can't be 2 indexes less than following numeral
		if (i > 0 && numerals_indexes[i - 1] + 2 < numerals_indexes[i])
			return false;
		// numeral can't be preceded and followed by equal lesser numerals
		if (i > 0 && i + 1 < ns.size() &&
			numerals_indexes[i - 1] < numerals_indexes[i] &&
			numerals_indexes[i - 1] == numerals_indexes[i + 1])
			return false;
		// numeral lesser than following numeral cannot be preceded by numeral lesser than following one
		if (i > 0 && i + 1 < ns.size() &&
			numerals_indexes[i] < numerals_indexes[i + 1] &&
			numerals_indexes[i - 1] < numerals_indexes[i + 1])
			return false;
	}
	
	return true;
}

int get_numeral_index(char numeral)
{
	for (int i = 0; i < roman_numerals.size(); ++i)
		if (toupper(numeral) == roman_numerals[i])
			return i;
	error("invalid numeral");
}

int main()
try
{
	Roman_int r{ "XCIX" };
	cout << "Roman " << r << " equals " << r.as_int() << '\n';
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}