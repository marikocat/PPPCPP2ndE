#include "Variable.h"

//------------------------------------------------------------------------------

double Symbol_table::get(string s)
// return the value of the Variable named s
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("get_value: undefined variable ", s);
}

//------------------------------------------------------------------------------

void Symbol_table::set(string s, double d)
// set the Variable named s to d
{
	for (Variable& v : var_table)
		if (v.name == s)
		{
			if (v.const_var) error(v.name, " is a const variable and cannot be assigned new value to");
			v.value = d;
			return;
		}
	error("set_value: undefined variable ", s);
}

//------------------------------------------------------------------------------

bool Symbol_table::is_declared(string var)
// is var already in var_table?
{
	for (const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}

//------------------------------------------------------------------------------

double Symbol_table::declare(string var, double val, bool cv)
// add (var,val) to var_table
{
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable(var, val, cv));
	return val;
}

//------------------------------------------------------------------------------

void Symbol_table::print()
{
	for (const Variable& v : var_table)
	{
		if (v.const_var)
			cout << "const ";
		cout << v.name << " = " << v.value << ";\n";
	}
}

//------------------------------------------------------------------------------