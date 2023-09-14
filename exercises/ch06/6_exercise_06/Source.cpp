/*
Grammar:

Sentence:
	Noun Verb // e.g., C++ rules
	Sentence Conjunction Sentence // e.g., Birds fly but fish swim
Conjunction:
	"and"
	"or"
	"but"
Noun:
	"birds"
	"fish"
	"C++"
Verb:
	"rules"
	"fly"
	"swim"
*/

#include "../std_lib_facilities.h"

vector<string> nouns{ "birds", "fish", "C++" };
vector<string> verbs{ "rules", "fly", "swim" };
vector<string> conjunctions{ "and", "or", "but" };

bool is_noun(string w)
{
	for (string s : nouns)
		if (s == w) return true;
	return false;
}

bool is_verb(string w)
{
	for (string s : verbs)
		if (s == w) return true;
	return false;
}

bool is_conjunction(string w)
{
	for (string s : conjunctions)
		if (s == w) return true;
	return false;
}

bool sentence()
{
	string w;
	cin >> w;
	if (!is_noun(w)) return false;

	cin >> w;
	if (!is_verb(w)) return false;

	cin >> w;
	if (w == ".") return true;
	if (!is_conjunction(w)) return false;
	return sentence();
}

int main()
try
{
	cout << "Enter a sentence terminated by a dot:\n";

	while (cin)
	{
		bool is_sentence = sentence();
		if (is_sentence)
			cout << "OK\n";
		else
			cout << "not OK\n";
		cout << "Enter next sentence:\n";
	}
}
catch (runtime_error& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}