#include "Roman_int.h"

const string roman_zero = "nulla";
const vector<char> roman_numerals = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
const vector<int> arabic_numerals = { 1, 5, 10, 50, 100, 500, 1000 };

const int max_numerals = 3999;

Roman_int::Roman_int() : n{ roman_zero }, i{ 0 } {}

Roman_int::Roman_int(const string& numerals) : n{ numerals }
{
	if (!are_valid_numerals(numerals)) error("are_valid_numerals(numerals): invalid numerals");

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

bool is_numeral(char numeral)
{
	for (char n : roman_numerals)
		if (numeral == n)
			return true;
	return false;
}

string to_numerals(int i)
{
	string numerals;

	if (i == 0) return roman_zero;

	if (i < 0)
	{
		numerals += "-";
		i = abs(i);
	}

	if (i > max_numerals) 
		error("can't represent with numerals value greater than ", max_numerals);

	if (i / 1000 > 0)
	{
		for (int j = 0; j < i / 1000; ++j)
		{
			numerals += roman_numerals[roman_numerals.size() - 1];
		}
		i -= (i / 1000) * 1000;
	}

	if (i / 100 > 0)
	{
		if (i / 100 <= 3)
		{
			for (int j = 0; j < i / 100; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 3];
			}
		}
		else if (i / 100 == 4)
		{
			numerals += roman_numerals[roman_numerals.size() - 3];
			numerals += roman_numerals[roman_numerals.size() - 2];
		}
		else if (i / 100 == 5)
		{
			numerals += roman_numerals[roman_numerals.size() - 2];
		}
		else if (i / 100 > 5 && i / 100 <= 8)
		{
			cout << "here\n";
			numerals += roman_numerals[roman_numerals.size() - 2];
			for (int j = 0; j < i / 100 - 5; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 3];
			}
		}
		else if (i / 100 == 9)
		{
			numerals += roman_numerals[roman_numerals.size() - 3];
			numerals += roman_numerals[roman_numerals.size() - 1];
		}
		i -= (i / 100) * 100;
	}

	if (i / 10 > 0)
	{
		if (i / 10 <= 3)
		{
			for (int j = 0; j < i / 10; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 5];
			}
		}
		else if (i / 10 == 4)
		{
			numerals += roman_numerals[roman_numerals.size() - 5];
			numerals += roman_numerals[roman_numerals.size() - 4];
		}
		else if (i / 10 == 5)
		{
			numerals += roman_numerals[roman_numerals.size() - 4];
		}
		else if (i / 10 > 5 && i / 10 <= 8)
		{
			cout << "here\n";
			numerals += roman_numerals[roman_numerals.size() - 4];
			for (int j = 0; j < i / 10 - 5; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 5];
			}
		}
		else if (i / 10 == 9)
		{
			numerals += roman_numerals[roman_numerals.size() - 5];
			numerals += roman_numerals[roman_numerals.size() - 3];
		}
		i -= (i / 10) * 10;
	}

	if (i > 1)
	{
		if (i <= 3)
		{
			for (int j = 0; j < i; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 7];
			}
		}
		else if (i == 4)
		{
			numerals += roman_numerals[roman_numerals.size() - 7];
			numerals += roman_numerals[roman_numerals.size() - 6];
		}
		else if (i == 5)
		{
			numerals += roman_numerals[roman_numerals.size() - 6];
		}
		else if (i > 5 && i <= 8)
		{
			cout << "here\n";
			numerals += roman_numerals[roman_numerals.size() - 6];
			for (int j = 0; j < i - 5; ++j)
			{
				numerals += roman_numerals[roman_numerals.size() - 7];
			}
		}
		else if (i == 9)
		{
			numerals += roman_numerals[roman_numerals.size() - 7];
			numerals += roman_numerals[roman_numerals.size() - 5];
		}
	}

	return numerals;
}