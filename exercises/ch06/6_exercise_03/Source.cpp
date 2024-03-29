/*
	Grammar:

	Expression:
		Term
		Expression "+" Term
		Expression "-" Term
	Term:
		Primary
		Term "*" Primary
		Term "/" Primary
	Primary:
		Number
		"(" Expression ")"
		"{" Expression "}"
		Primary "!"
	Number:
		floating-point-literal
*/

#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

class Token
{
public:
	char kind;
	double value;
	Token(char ch)
		: kind(ch), value(0) {}
	Token(char ch, double val)
		: kind(ch), value(val) {}
};

//------------------------------------------------------------------------------

class Token_stream
{
	bool full;
	Token buffer;
public:
	Token_stream();
	Token get();
	void putback(Token t);
};

//------------------------------------------------------------------------------

Token_stream::Token_stream()
	: full(false), buffer(0)
{

}

//------------------------------------------------------------------------------

Token Token_stream::get()    // read a token from cin
{
	if (full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)

	switch (ch) {
	case ';':    // for "print"
	case 'q':    // for "quit"
	case '(': case ')': case '{': case '}':
	case '!':
	case '+': case '-': case '*': case '/':
		return Token(ch);        // let each character represent itself
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);         // put digit back into the input stream
		double val;
		cin >> val;              // read a floating-point number
		return Token('8', val);   // let '8' represent "a number"
	}
	default:
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

Token_stream ts;

//------------------------------------------------------------------------------

double expression();

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

double primary()
{
	Token t = ts.get();
	double d = 0;
	switch (t.kind)
	{
	case '(':
	{
		d = expression();
		t = ts.get();
		if (t.kind != ')') error("')' expected");
		break;
	}
	case '{':
	{
		d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}' expected");
		break;
	}
	case '8':
	{
		d = t.value;
		break;
	}
	default:
		error("primary expected");
	}

	// check for Primary "!" case
	t = ts.get();
	if (t.kind != '!')
	{
		
		ts.putback(t);
		return d;
	}
	return factorial(d);
}

//------------------------------------------------------------------------------

double term()
{
	double left = primary();
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
		{
			double d = primary();
			if (d == 0) error("divide by zero");
			left /= d;
			t = ts.get();
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
	Token t = ts.get();
	while (true)
	{
		switch (t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

//------------------------------------------------------------------------------

int main()
try
{
	double val = 0;
	while (cin)
	{
		Token t = ts.get();

		if (t.kind == 'q') break;
		if (t.kind == ';')
		{
			cout << "=" << val << '\n';
			continue;
		}
		else
			ts.putback(t);
		val = expression();
	}
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown exception\n";
	return 2;
}

//------------------------------------------------------------------------------
