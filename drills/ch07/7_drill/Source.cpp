/*
	calculator08buggy.cpp

	Helpful comments removed.

	We have inserted 3 bugs that the compiler will catch and 3 that it won't.

	The grammar for input is:

	Calculation:
		Statement
		Print
		Quit
		Calculation Statement

	Statement:
		Declaration
		Expression

	Declaration:
		"let" name "=" Expression

	Print:
		";"

	Quit:
		"q"

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term

	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
		Term "%" Primary

	Primary:
		Number
		Name
		"(" Expression ")"
		"-" Primary
		"+" Primary
		sqrt Primary
		pow "(" Expression "," int(Expression) ")"

	Number:
		floating-point-literal

	Input comes from cin through the Token_stream called ts.
*/

#include "../std_lib_facilities.h"

struct Token
{
	char kind;
	double value;
	string name;
	Token(char ch) :kind(ch), value(0) { }
	Token(char ch, double val) :kind(ch), value(val) { }
	Token(char ch, string n) :kind(ch), name(n) { }
};

class Token_stream
{
	bool full;
	Token buffer;
public:
	Token_stream() :full(0), buffer(0) { }

	Token get();		// get a Token
	void unget(Token);	// put a Token back

	void ignore(char);	// discard characters up to and including a c
};

const char let = '#';		// declaration Token
const char quit = 'Q';		// quit Token
const char print = ';';		// print Token
const char number = '8';	// number Token
const char name = 'a';		// name Token
const char sqroot = 'S';	// square root Token
const char power = 'P';		// power Token

const string declkey = "let";
const string quitkey = "exit";
const string sqrootkey = "sqrt";
const string powkey = "pow";
const string prompt = "> ";
const string result = "= ";

Token Token_stream::get()
// read characters from cin and compose a Token

{
	if (full) // check if we already have a Token ready
	{ 
		full = false; 
		return buffer;
	}

	char ch;
	cin >> ch;
	switch (ch) {
	case print:
	case let:
	case '(':
	case ')':
	case ',':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '=':
		return Token(ch);	// let each character represent itself
	case '.':	// a floating-point-literal can start with a dot
	case '0':	// numeric literal
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
	{
		cin.unget();	// put digit back into the input stream
		double val;
		cin >> val;	// read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch)) {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.unget();
			if (s == declkey) return Token(let);		// declaration keyword
			if (s == quitkey) return Token(quit);		// quit keyword
			if (s == sqrootkey) return Token(sqroot);	// square root key
			if (s == powkey) return Token(power);		// power key
			return Token(name, s);
		}
		error("Bad token");
	}
}

void Token_stream::unget(Token t)
{
	if (full) error("putback() into a full buffer");
	buffer = t;
	full = true;
}

void Token_stream::ignore(char c)
// c represents the kind of Token
{
	// first look in buffer:
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	// now search input:
	char ch;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable
{
	string name;
	double value;
	Variable(string n, double v) :name(n), value(v) { }
};

vector<Variable> names;

double get_value(string s)
// return the value of the Variable named s
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined variable name ", s);
}

void set_value(string s, double d)
// set the Variable named s to d
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			names[i].value = d;
			return;
		}
	error("set: undefined variable name ", s);
}

bool is_declared(string s)
// is var already in var_table?
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

double define_name(string var, double val)
// add (var,val) to var_table
{
	if (is_declared(var)) error(var, " declared twice");
	names.push_back(Variable(var, val));
	return val;
}

Token_stream ts;

double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case '+':
		return primary();
	case number:
		return t.value;				// return the number’s value
	case name:
		return get_value(t.name);	// return the variable's value
	case sqroot:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		ts.unget(t);
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

double term()
{
	double left = primary();
	while (true)
	{
		Token t = ts.get();
		switch (t.kind)
		{
		case '*':
			left *= primary();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary());
			if (i2 == 0) error("%: divide by zero");
			left = i1 % i2;
			break;
		}
		default:
			ts.unget(t);
			return left;
		}
	}
}

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
			ts.unget(t);
			return left;
		}
	}
}

double declaration()
// assume we have seen "let”
// handle: name = expression
// declare a variable called "name” with the initial value "expression”
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;
	if (is_declared(var_name)) error(var_name, " declared twice");

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression();
	names.push_back(Variable(var_name, d));
	return d;
}

double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void calculate()
{
	while (true) try {
		cout << prompt;							// print prompt
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	// first discard all “prints”
		if (t.kind == quit) return;
		ts.unget(t);
		cout << result << statement() << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()
try
{
	// predefine names:
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);
	define_name("k", 1000);

	calculate();
	return 0;
}
catch (exception& e)
{
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...)
{
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}