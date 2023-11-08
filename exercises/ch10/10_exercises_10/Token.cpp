#include "Token.h"

//------------------------------------------------------------------------------

Token_stream::Token_stream(istream& is)
	: full(false), buffer(0), input_stream(is)
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
	// cin >> ch;    // note that >> skips whitespace (space, newline, tab, etc.)
	input_stream.get(ch);

	switch (ch)
	{
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
		input_stream.putback(ch);         // put digit back into the input stream
		double val;
		input_stream >> val;              // read a floating-point number
		return Token(number, val);
	}
	default:
		if (isalpha(ch) || ch == '_')
		{
			string s;
			s += ch;
			while (input_stream.get(ch) && (isalpha(ch) || isdigit(ch) || ch == '_')) s += ch;
			input_stream.putback(ch);
			if (s == declkey) return Token(let);		// declaration keyword
			if (s == quitkey) return Token(quit);		// quit keyword
			if (s == sqrootkey) return Token(sqroot);	// square root key
			if (s == powkey) return Token(power);		// power key
			if (s == constvkey) return Token(constv);	// const variable key
			if (s == helpkey) return Token(help);
			if (s == stablekey) return Token(stable);
			if (s == fromkey) return Token(from);
			if (s == tokey) return Token(to);
			return Token(name, s);
		}
		else if (isspace(ch))
		{
			if (ch == '\n')
				return Token(print);
			else
				return get();
		}
		if (input_stream.eof()) return Token(quit);
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
	while (input_stream.get(ch))
		if (ch == c || ch == '\n') return;
}

//------------------------------------------------------------------------------