/*
	Simple calculator

	This program implements a basic expression calculator.
	It supports basic arithmetic operations,
	including +, -, *, /, %, and !, sqrt(x) and pow(x) functions.
	Users may declare their own constants and variables
	and assign new values to variables.

	Also this program has four commands,
	including Print, Quit, Help, Symbols table.

	Input from cin; output to cout.

	The grammar for input is:

	Calculation:
		Command
		Statement
		Calculation Statement

	Coomand:
		Print
		Quit
		Help
		Symbols table

	Print:
		";"
		"\n"

	Quit:
		"quit"

	Help:
		"help"

	Symbols table
		"table"

	Statement:
		Declaration
		Assignment
		Expression

	Declaration:
		"let" Name "=" Expression
		"const" Name "=" Expression

	Assignment:
		Name "=" Expression

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term

	Term:
		Secondary
		Term "*" Secondary
		Term "/" Secondary
		Term "%" Secondary

	Secondary:
		Primary
		Primary "!"

	Primary:
		Number
		Name
		"(" Expression ")"
		"{" Expression "}"
		"-" Primary
		"+" Primary
		sqrt Primary
		pow "(" Expression "," int(Expression) ")"

	Number:
		floating-point-literal

	Input comes from cin through the Token_stream called ts.
*/

#include "../std_lib_facilities.h"
#include "Token.h"
#include "Variable.h"

//------------------------------------------------------------------------------

Symbol_table st;

//------------------------------------------------------------------------------

double expression(Token_stream& ts);

//------------------------------------------------------------------------------

double primary(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '{':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return d;
	}
	case number:
		return t.value; // return the number�s value
	case name:
		return st.get(t.name); // return the variable's value
	case '-':
		return -primary(ts);
	case '+':
		return primary(ts);
	case sqroot:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		ts.putback(t);
		double d = primary(ts);
		if (d < 0) error("square root of negative number");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int n = narrow_cast<int>(expression(ts));
		t = ts.get();
		if (t.kind != ')') error("'(' expected");
		return pow(d, n);
	}
	default:
		error("primary expected");
	}
}

//------------------------------------------------------------------------------

double factorial(double d)
{
	int n = narrow_cast<int>(d);

	if (n < 0) error("factorial not defined for negative values");
	if (n > 31) error("factorial defined only for ints (too large)");

	if (n == 0)
		return 1;
	else
		return n * factorial(n - 1);
}

//------------------------------------------------------------------------------

double secondary(Token_stream& ts)
{
	double left = primary(ts);
	while (true)
	{
		Token t = ts.get();
		if (t.kind == '!')
			left = factorial(left);
		else
		{
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

double term(Token_stream& ts)
{
	double left = secondary(ts);
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '*':
			left *= secondary(ts);
			break;
		case '/':
		{
			double d = secondary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(secondary(ts));
			if (i2 == 0) error("%: divide by zero");
			left = i1 % i2;
			break;
		}
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

double expression(Token_stream& ts)
{
	double left = term(ts);
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '+':
			left += term(ts);
			break;
		case '-':
			left -= term(ts);
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

double declaration(Token_stream& ts, bool cv)
// assume we have seen "let�
// handle: name = expression
// declare a variable called "name� with the initial value "expression�
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression(ts);
	st.declare(var_name, d, cv);
	return d;
}

//------------------------------------------------------------------------------

double assignment(Token_stream& ts, string n)
{
	double d = expression(ts);
	st.set(n, d);
	return d;
}

//------------------------------------------------------------------------------

double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind)
	{
	case constv:
		return declaration(ts, true);
	case let:
		return declaration(ts, false);
	case name:
	{
		char ch;
		while (cin.get(ch) && isspace(ch) && ch != '\n');
		if (ch == '=')
			return assignment(ts, t.name);
		else
			cin.putback(ch);
	}
	default:
		ts.putback(t);
		return expression(ts);
	}
}

//------------------------------------------------------------------------------

void clean_up_mess(Token_stream& ts)
{
	ts.ignore(print);
}

//------------------------------------------------------------------------------

void print_help()
{
	cout << "to quit enter 'quit'\n";
	cout << "to print help instructions enter 'help'\n";
	cout << "to print symbol table enter 'table'\n";
	cout << "to print result press ';' or press Enter\n";
	cout << "to define a variable use 'let' or '#'\n";
	cout << "to define a constant use 'const'\n";
	cout << "supported operators: +, -, *, /, %, !\n";
	cout << "supported functions: sqrt(x), pow(x, n)\n";
}

//------------------------------------------------------------------------------

void calculate()
{
	Token_stream ts(cin);
	while (true)
		try
	{
		cout << prompt; // print prompt
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // first discard all �prints�
		if (t.kind == quit) return;
		if (t.kind == help)
		{
			print_help();
			continue;
		}
		if (t.kind == stable)
		{
			st.print();
			continue;
		}
		ts.putback(t);
		cout << result << statement(ts) << '\n';
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
		clean_up_mess(ts);
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	// predefine names:
	st.declare("pi", 3.1415926535, true);
	st.declare("e", 2.7182818284, true);
	st.declare("k", 1000, true);

	calculate();

	keep_window_open();
	return 0;
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	keep_window_open("~~");
	return 1;
}
catch (...)
{
	cerr << "unknown exception\n";
	keep_window_open("~~");
	return 2;
}

//------------------------------------------------------------------------------