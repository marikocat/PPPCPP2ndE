#pragma once
#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

class Variable
{
public:
	string name;
	double value;
	bool const_var;
	Variable(string n, double v, bool cv) : name(n), value(v), const_var(cv) {}
};

//------------------------------------------------------------------------------

class Symbol_table
{
	vector<Variable> var_table;
public:
	double get(string s);
	void set(string s, double d);
	bool is_declared(string var);
	double declare(string var, double val, bool cv);
	void print();
};

//------------------------------------------------------------------------------