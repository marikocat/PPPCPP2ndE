/*
	Simple calculator

	This program implements a basic expression calculator.
	Input from cin; output to cout.

	The grammar for input is:

	Calculation:
		Statement
		Print
		Quit
		Calculation Statement

	Statement:
		Declaration
		Assignment
		Expression

	Print:
		";"

	Quit:
		"q"
		"exit"

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

//------------------------------------------------------------------------------

const char number = '8';	// t.kind==number means that t is a number Token
const char quit = 'q';		// t.kind==quit means that t is a quit Token
const char print = ';';		// t.kind==print means that t is a print Token
const char name = 'a';		//name token
const char let = '#';		// declaration token
const char sqroot = 'S';	// square root Token
const char power = 'P';		// power Token
const char constv = 'C';

const string declkey = "let";
const string quitkey = "exit";
const string sqrootkey = "sqrt";
const string powkey = "pow";
const string constvkey = "const";
const string prompt = "> ";
const string result = "= "; // used to indicate that what follows is a result

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;
	double value;
	string name;
	Token(char ch) : kind(ch), value(0) {}
	Token(char ch, double val) : kind(ch), value(val) {}
	Token(char ch, string n) : kind(ch), value(0), name(n) {}
};

//------------------------------------------------------------------------------

class Token_stream
{
	bool full;
	Token buffer;
public:
	Token_stream();
	Token get();			// get a Token
	void putback(Token t);  // put a Token back
	void ignore(char c);	// discard characters up to and including a c
};

//------------------------------------------------------------------------------

Token_stream::Token_stream()
	: full(false), buffer(0)
{

}

//------------------------------------------------------------------------------

Token Token_stream::get()
// read characters from cin and compose a Token
{
	if (full) // check if we already have a Token ready
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch)
	{
	case quit:
	case print:
	case let:
	case '(':
	case ')':
	case '{':
	case '}':
	case ',':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
	case '=':
		return Token(ch);        // let each character represent itself
	case '.':					 // a floating-point-literal can start with a dot
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':		// numeric literal
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_')
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token{ let };		// declaration keyword
			if (s == quitkey) return Token(quit);		// quit keyword
			if (s == sqrootkey) return Token(sqroot);	// square root key
			if (s == powkey) return Token(power);		// power key
			if (s == constvkey) return Token(constv);	// const variable key
			return Token{ name, s };
		}
		error("Bad token");
	}
}

//------------------------------------------------------------------------------

void Token_stream::putback(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

//------------------------------------------------------------------------------

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind)
	{
		full = false;
		return;
	}
	full = false;

	// now search input:
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

//------------------------------------------------------------------------------

Token_stream ts;

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

vector<Variable> var_table;

//------------------------------------------------------------------------------

double get_value(string s)
// return the value of the Variable named s
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("get_value: undefined variable ", s);
}

//------------------------------------------------------------------------------

void set_value(string s, double d)
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

bool is_declared(string var)
// is var already in var_table?
{
	for (const Variable& v : var_table)
		if (v.name == var) return true;
	return false;
}

//------------------------------------------------------------------------------

double define_name(string var, double val, bool cv)
// add (var,val) to var_table
{
	if (is_declared(var)) error(var, " declared twice");
	var_table.push_back(Variable(var, val, cv));
	return val;
}

//------------------------------------------------------------------------------

double expression();

//------------------------------------------------------------------------------

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '{':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		return d;
	}
	case number:
		return t.value; // return the number’s value
	case name:
		return get_value(t.name); // return the variable's value
	case '-':
		return -primary();
	case '+':
		return primary();
	case sqroot:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		ts.putback(t);
		double d = primary();
		if (d < 0) error("square root of negative number");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = expression();
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int n = narrow_cast<int>(expression());
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

double secondary()
{
	double left = primary();
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

double term()
{
	double left = secondary();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '*':
			left *= secondary();
			break;
		case '/':
		{
			double d = secondary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(secondary());
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

double expression()
{
	double left = term();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '+':
			left += term();
			break;
		case '-':
			left -= term();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

double declaration(bool cv)
// assume we have seen "let”
// handle: name = expression
// declare a variable called "name” with the initial value "expression”
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	define_name(var_name, d, cv);
	return d;
}

//------------------------------------------------------------------------------

double assignment(string n)
{
	double d = expression();
	set_value(n, d);
	return d;
}

//------------------------------------------------------------------------------

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case constv:
		return declaration(true);
	case let:
		return declaration(false);
	case name:
		char ch;
		cin >> ch;
		if (ch == '=')
			return assignment(t.name);
		else
			cin.putback(ch);
	default:
		ts.putback(t);
		return expression();
	}
}

//------------------------------------------------------------------------------

void clean_up_mess()
{
	ts.ignore(print);
}

//------------------------------------------------------------------------------

void calculate()
{
	while (cin)
		try
	{
		cout << prompt; // print prompt
		Token t = ts.get();
		while (t.kind == print) t = ts.get(); // first discard all “prints”
		if (t.kind == quit) return;
		ts.putback(t);
		cout << result << statement() << '\n';
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
		clean_up_mess();
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	// predefine names:
	define_name("pi", 3.1415926535, true);
	define_name("e", 2.7182818284, true);
	define_name("k", 1000, true);

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