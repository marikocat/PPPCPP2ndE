#pragma once
#include "..\std_lib_facilities.h"

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

ostream& operator<<(ostream& os, const Roman_int& ri);
istream& operator>>(istream& is, Roman_int& ri);

bool are_valid_numerals(const string& ns);
int get_numeral_index(char numeral);
bool is_numeral(char numeral);
string to_numerals(int a);