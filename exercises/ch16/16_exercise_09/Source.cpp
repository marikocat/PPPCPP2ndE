#include "Gui.h"
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
Declaration:
	let Name = Expression
	const Name = Expression
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
	Name
	Assignment
	( Expression )
	– Primary
	sqrt Primary
	pow Primary ',' Primary
Number:
	floating-point-literal
Assignment:
	Name = Expression

Input comes from cin through the Token_stream called ts.
*/

struct Token {
	char kind; // what kind of token
	double value; // for numbers: a value
	string name; // for variable names: a name
	Token(char ch) :kind(ch), value(0) { } // make a Token from a char
	Token(char ch, double val) :kind(ch), value(val) { } // make a Token from a char and a double
	Token(char ch, string n) :kind(ch), name(n), value(0) { } // make a Token from a char and a name
};

class Token_stream {
	bool full; // is there a Token in the buffer?
	Token buffer; // where we store a 'unget' Token
	istream& input;
public:
	Token_stream(istream& i) :full{ false }, buffer{ 0 }, input{ i } { }

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

const string constkey = "const"; // definition of const vars
const string declkey = "#"; // declaration keyword
const string quitkey = "exit"; // quit keyword

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
	ch = input.get();
	if (input.eof())
		return Token(print);
	cout << "ch: " << ch << "\n";

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
	case '.':
	case '0':
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
		input.unget();
		double val;
		input >> val;
		return Token(number, val);
	}
	case '#':
		return Token{ let };
	default:
		if (isalpha(ch) || ch == '_') {
			string s;
			s += ch;
			while (input.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			input.unget();
			// if (s == "let") return Token{ let };
			if (s == quitkey) return Token{ quit };
			if (s == constkey) return Token{ constV };
			if (s == "sqrt") return Token{ sqRoot };
			if (s == "pow") return Token{ power };
			return Token{ name, s };
		}
		else if (isspace(ch)) {
			if (ch == '\n')
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
	while (ch != c && ch != '\n')
		ch = input.get();
	return;
}

//------------------------------------------------------------------------------

struct Variable {
	string name;
	double value;
	bool constVar;
	Variable(string n, double v, bool cv) :name(n), value(v), constVar(cv) { }
};

class Symbol_table {
	vector<Variable> names;
public:
	double get_value(string s);
	void set_value(string s, double d);
	bool is_declared(string s);
	double define_name(string var, double val, bool cv);
};

double Symbol_table::get_value(string s)
{
	for (int i = 0; i < names.size(); ++i)
		if (names[i].name == s) return names[i].value;
	error("get: undefined variable name ", s);
}

void Symbol_table::set_value(string s, double d)
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

double Symbol_table::define_name(string var, double val, bool cv)
{
	if (is_declared(var)) error(var, " declared twice");
	names.push_back(Variable(var, val, cv));
	return val;
}

Symbol_table st;

//------------------------------------------------------------------------------

double expression(Token_stream& ts);

double assignment(Token_stream& ts, string n)
{
	double d = expression(ts);
	st.set_value(n, d);
	return d;
}

double primary(Token_stream& ts) // read and evaluate a Primary
{
	Token t = ts.get();
	switch (t.kind) {
	case '(':
	{
		double d = expression(ts);
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		return d;
	}
	case '-':
		return -primary(ts);
	case number:
		return t.value; // return the number's value
	case name:
	{
		Token temp = ts.get();
		if (temp.kind == '=') {
			return assignment(ts, t.name);
		}
		ts.unget(temp);
		return st.get_value(t.name);
	}
	case sqRoot:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		ts.unget(t);
		double d = primary(ts);
		if (d < 0) error("the square root of a negative number");
		return sqrt(d);
	}
	case power:
	{
		t = ts.get();
		if (t.kind != '(') error("'(' expected");
		double d = narrow_cast<int>(expression(ts));
		t = ts.get();
		if (t.kind != ',') error("',' expected");
		int n = narrow_cast<int>(expression(ts));
		t = ts.get();
		if (t.kind == ')') return pow(d, n);
		else error("Expected ')'");
	}
	default:
		error("primary expected");
	}
}

double term(Token_stream& ts) // read and evaluate a Term
{
	double left = primary(ts);
	while (true) {
		Token t = ts.get();
		switch (t.kind) {
		case '*':
			left *= primary(ts);
			break;
		case '/':
		{
			double d = primary(ts);
			if (d == 0) error("divide by zero");
			left /= d;
			break;
		}
		case '%':
		{
			int i1 = narrow_cast<int>(left);
			int i2 = narrow_cast<int>(primary(ts));
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

double expression(Token_stream& ts) // read and evaluate a Expression
{
	double left = term(ts); // read and evaluate a Term
	while (true) {
		Token t = ts.get(); // get the next token
		switch (t.kind) {
		case '+':
			left += term(ts); // evaluate Term and add
			break;
		case '-':
			left -= term(ts); // evaluate Term and subtract
			break;
		default:
			ts.unget(t);
			return left; // finally: no more + or -: return the answer
		}
	}
}

double declaration(Token_stream& ts, bool cv)
{
	Token t = ts.get();
	if (t.kind != name) error("name expected in declaration");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("= missing in declaration of ", var_name);

	double d = expression(ts);
	st.define_name(var_name, d, cv);
	return d;
}

double statement(Token_stream& ts)
{
	Token t = ts.get();
	switch (t.kind) {
	case let:
		return declaration(ts, false);
	case constV:
		return declaration(ts, true);
	default:
		ts.unget(t);
		return expression(ts);
	}
}

void clean_up_mess(Token_stream& ts)
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

void calculate(istream& is, ostream& os)
{
	Token_stream ts{ is }; // provides get() and unget()
	while (true) try {
		//cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();
		if (t.kind == quit) return;
		if (t.kind == help) {
			printHelp();
			continue;
		}
		ts.unget(t);
		os << statement(ts);
		break;
	}
	catch (runtime_error& e) {
		cout << e.what() << endl;
		clean_up_mess(ts);
	}
}

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	In_box in_box;
	Out_box out_box;
	Button calculate_button;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void press_calculate();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	in_box{Point{150, 100}, 100, 20, "Input: "},
	out_box{Point{300, 100}, 100, 20, "Result: "},
	calculate_button{Point{500, 100}, 70, 20, "Calculate",
		[](Address, Address pw) {reference_to<My_window>(pw).press_calculate(); } }
{
	attach(next_button);
	attach(quit_button);
	attach(in_box);
	attach(out_box);
	attach(calculate_button);
}

void My_window::wait_for_button()
{
	while (!next_button_pushed && !quit_button_pushed)
	{
		Fl::wait();
	}
	if (next_button_pushed)
	{
		next_button_pushed = false;
		Fl::redraw();
	}
}

void My_window::cb_next(Address, Address pw)
{
	reference_to<My_window>(pw).next();
}

void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::next()
{
	next_button_pushed = true;
}

void My_window::quit()
{
	quit_button_pushed = true;
	hide();
}

void My_window::press_calculate()
{
	string s = in_box.get_string();
	istringstream iss{ s };

	ostringstream oss;
	calculate(iss, oss);
	out_box.put(oss.str());
	redraw();
}

int main()
try
{
	My_window win{ Point{100, 100}, 600, 400, "My window" };
	win.wait_for_button();
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}