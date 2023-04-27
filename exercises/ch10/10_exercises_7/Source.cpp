/*
Simple calculator

Revision history:
Revised by Bjarne Stroustrup November 2013
Revised by Bjarne Stroustrup May 2007
Revised by Bjarne Stroustrup August 2006
Revised by Bjarne Stroustrup August 2004
Originally written by Bjarne Stroustrup
(bs@cs.tamu.edu) Spring 2004.

This program implements a basic expression calculator.
Input from cin; output to cout.
The grammar for input is:

Calculation:
	Statement
	Print
	Quit
	Calculation Statement

Print:
	;

Quit:
	q

Statement:
	Declaration
	Expression
	Assignment

Declaration:
	"let" Name "=" Expression
	"const" Name "=" Expression

Assignment:
	Name "=" Expression

Expression:
	Term
	Expression + Term
	Expression – Term
Term:
	Primary
	Term * Primary
	Term / Primary
	Term % Primary
Primary:
	Number
	Variable Name
	( Expression )
	– Primary
	sqrt Primary
	pow Primary ',' Primary
Number:
	floating-point-literal

Input comes from cin through the Token_stream called ts.
*/

#include "..\std_lib_facilities.h"
#include "Roman_int.h"

struct Token {
	char kind; // what kind of token
	int value; // for numbers: a value
	string name; // for variable names: a name
	Token(char ch) :kind(ch), value(0) { } // make a Token from a char
	Token(char ch, int val) :kind(ch), value(val) { } // make a Token from a char and a double
	Token(char ch, string n) :kind(ch), name(n), value(0) { } // make a Token from a char and a name
};

class Token_stream {
	bool full; // is there a Token in the buffer?
	Token buffer; // where we store a 'unget' Token
public:
	Token_stream() :full(0), buffer(0) { }

	Token get(); // get a Token
	void unget(Token t); // put a Token back

	void ignore(char c); // discard characters up to and including a c
};

const char constV = 'C';
const char let = 'L';
const char quit = 'q';
const char help = 'h';
const char print = ';';
const char number = '8'; // t.kind == number means that t is a number Token
const char name = 'a';
const char sqRoot = 'S';
const char power = 'P';
const char newline = '\n';

const string constkey = "const"; // definition of const vars
const string declkey = "#"; // declaration keyword
const string quitkey = "exit"; // quit keyword
const string sqrtkey = "sqrt";
const string powkey = "pow";

void Token_stream::unget(Token t) {
	if (full) error("unget() into a full buffer");
	buffer = t;
	full = true;
}

Token Token_stream::get()
{
	if (full) { full = false; return buffer; }
	char ch;
	// cin >> ch; // note that >> skips whitespace (space, newline, tab, etc.)
	ch = cin.get();

	switch (ch) {
	case print:
	case quit:
	case help:
	case '=':
	case '(':
	case ')':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case ',':
		return Token(ch); // let each character represent itself
	case 'I':
	case 'V':
	case 'X':
	case 'L':
	case 'C':
	case 'D':
	case 'M':
	{
		string numerals;
		numerals += ch;
		while (cin.get(ch) && is_numeral(ch)) numerals += ch;
		cin.unget();
		Roman_int ri{ numerals };
		return Token{ number, ri.as_int() };
	}
	case '#':
		return Token{ let };
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			cin.unget();
			// if (s == "let") return Token{ let };
			if (s == quitkey) return Token{ quit };
			if (s == constkey) return Token{ constV };
			if (s == sqrtkey) return Token{ sqRoot };
			if (s == powkey) return Token{ power };
			return Token{ name, s };
		}
		else if (isspace(ch)) {
			if (ch == newline)
				return Token{ print };
			else return get();
		}
		error("Bad token");
	}
}

void Token_stream::ignore(char c)
{
	if (full && c == buffer.kind) {
		full = false;
		return;
	}
	full = false;

	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

struct Variable {
	string name;
	int value;
	bool constVar;
	Variable(string n, int v, bool cv) :name(n), value(v), constVar(cv) { }
};

class Symbol_table {
	vector<Variable> names;
public:
	int get_value(string s);
	void set_value(string s, int d);
	bool is_declared(string s);
	int define_name(string var, int val, bool cv);
};

// vector<Variable> names;

int Symbol_table::get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined variable name ", s);
}

void Symbol_table::set_value(string s, int d)
{
	for (int i = 0; i <= names.size(); ++i)
		if (names[i].name == s) {
			if (names[i].constVar) error(names[i].name, " is const variable and cannot be redefined");
			names[i].value = d;
			return;
		}
	error("set: undefined variable name ", s);
}

bool Symbol_table::is_declared(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return true;
	return false;
}

int Symbol_table::define_name(string var, int val, bool cv)
{
	if (is_declared(var)) error(var, " declared twice");
	names.push_back(Variable(var, val, cv));
	return val;
}

Symbol_table st;

Token_stream ts; // provides get() and unget()

int expression();

int primary() // read and evaluate a Primary
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		int d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary();
	case number:
		return t.value; // return the number's value
	case name:
		return st.get_value(t.name);
	case sqRoot:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		ts.unget(t);
		int d = primary();
		if (d < 0) error("the square root of a negative number");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		int d = expression();
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int n = expression();
		t = ts.get();
		if (t.kind == ')') return pow(d, n);
		else error("Expected ')'");
	}
	default:
		error("primary expected");
	}
}

int term() // read and evaluate a Term
{
	int left = primary();
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary();
			break;
		case '/':
		{
			int d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = left;
			int i2 = primary();
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

int expression() // read and evaluate a Expression
{
	int left = term(); // read and evaluate a Term
	while (true) {
		Token t = ts.get(); // get the next token
		switch (t.kind) {
		case '+':
			left += term(); // evaluate Term and add
			break;
		case '-':
			left -= term(); // evaluate Term and subtract
			break;
		default:
			ts.unget(t);
			return left; // finally: no more + or -: return the answer
		}
	}
}

int declaration(bool cv)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	int d = expression();
	st.define_name(var_name, d, cv);
	return d;
}

int assignment(string n)
{
	int d = expression();
	st.set_value(n, d);
	return d;
}

int statement()
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(false);
	case constV:
		return declaration(true);
	case name:
	{
		char temp = 0;
		cin >> temp;
		if (temp == '=') {
			return assignment(t.name);
		}
		else {
			cin.putback(temp);
		}
	}
	default:
		ts.unget(t);
		return expression();
	}
}

void clean_up_mess()
{
	ts.ignore(print);
}

void printHelp()
{
	cout << "to quit press 'q' (or type 'exit')\n";
	cout << "to print instructions press 'h'\n";
	cout << "to print result press ';' or Enter\n";
	cout << "to define a variable use 'let'\n";
	cout << "to define a const variable use 'const'\n";
}

const string prompt = "> ";
const string result = "= ";

void calculate()
{
	while (true) try {
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		if (t.kind == help) {
			printHelp();
			continue;
		}
		ts.unget(t);
		//cout << result << statement() << endl;
		cout << result << to_numerals(statement()) << endl;
	}
	catch (runtime_error& e) {
		cerr << e.what() << endl;
		clean_up_mess();
	}
}

int main()

try {
	st.define_name("k", 1000, true);

	calculate();
	return 0;
}
catch (exception& e) {
	cerr << "exception: " << e.what() << endl;
	char c;
	while (cin >> c && c != ';');
	return 1;
}
catch (...) {
	cerr << "exception\n";
	char c;
	while (cin >> c && c != ';');
	return 2;
}