#pragma once
#include "../std_lib_facilities.h"

//------------------------------------------------------------------------------

const char number = '8';	// t.kind==number means that t is a number Token
const char quit = 'Q';		// t.kind==quit means that t is a quit Token
const char help = 'H';		// help Token
const char print = ';';		// t.kind==print means that t is a print Token
const char name = 'a';		//name token
const char let = '#';		// declaration token
const char sqroot = 'R';	// square root Token
const char power = 'P';		// power Token
const char constv = 'C';	// const Token
const char stable = 'S';	// symbol table Token
const char from = 'F';		// from file Token
const char to = 'T';		// to file Token

const string declkey = "let";
const string quitkey = "quit";
const string helpkey = "help";
const string sqrootkey = "sqrt";
const string powkey = "pow";
const string constvkey = "const";
const string stablekey = "table";
const string fromkey = "from";
const string tokey = "to";
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
	istream& input_stream;
public:
	Token_stream(istream& is);
	Token get();			// get a Token
	void putback(Token t);  // put a Token back
	void ignore(char c);	// discard characters up to and including a c
};

//------------------------------------------------------------------------------