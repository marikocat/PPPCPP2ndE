#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>
using namespace std;

using Line = vector<char>; // a line is a vector of characters

class Text_iterator { // keep track of line and character position within line
	list<Line>::iterator ln;
	Line::iterator pos;
public:
	typedef forward_iterator_tag iterator_category;
	typedef char value_type;
	typedef size_t difference_type;
	typedef char* pointer;
	typedef char& reference;

	// start the iterator at line ll's character position pp:
	Text_iterator(list<Line>::iterator ll, Line::iterator pp)
		: ln{ ll }, pos{ pp }{}

	char& operator*() { return *pos; }
	Text_iterator& operator++();
	Text_iterator& operator--();

	bool operator==(const Text_iterator& other) const
	{
		return ln == other.ln && pos == other.pos;
	}
	bool operator!=(const Text_iterator& other) const
	{
		return !(*this == other);
	}
};

Text_iterator& Text_iterator::operator++()
{
	++pos;
	if (pos == (*ln).end())
	{
		++ln;
		pos = (*ln).begin();
	}
	return *this;
}

Text_iterator& Text_iterator::operator--()
{
	if (pos == (*ln).begin())
	{
		--ln;
		pos = (*ln).end();
	}
	if (pos == (*ln).end())
	{
		--pos;
	}
	--pos;
	return *this;
}

struct Document {
	list<Line> lines; // a document is a list of lines

	Document() { lines.push_back(Line{}); }

	Text_iterator begin() // first character of first line
	{
		return Text_iterator(lines.begin(), (*lines.begin()).begin());
	}

	Text_iterator end() // one beyond the last character of the last line
	{
		auto last = lines.end();
		--last; // we know that the document is not empty
		return Text_iterator(last, (*last).end());
	}
};

istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch); ) {
		d.lines.back().push_back(ch); // add the character
		if (ch == '\n')
			d.lines.push_back(Line{}); // add another line
	}
	if (d.lines.back().size()) d.lines.push_back(Line{}); // add final empty line
	return is;
}

void print(Document& d)
{
	for (auto p : d) cout << p;
	cout << '\n';
}

template<typename Iter>
void my_advance(Iter& p, int n)
{
	while (n > 0) { ++p; --n; }
	while (n < 0) { --p; ++n; }
}

void erase_line(Document& d, int n)
{
	if (n < 0 || d.lines.size() - 1 <= n) return;
	auto p = d.lines.begin();
	my_advance(p, n);
	d.lines.erase(p);
}

bool match(Text_iterator first, Text_iterator last, const string& s)
{
	int i = 0;
	for (; i < s.size() && first != last; ++i, ++first)
	{
		if (*first != s[i])
		{
			return false;
		}
	}
	return i == s.size();
}

Text_iterator find_text(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;    // can't find an empty string
	char first_char = s[0];
	while (true) {
		Text_iterator p = find(first, last, first_char);
		if (p == last) {
			return p;
		}
		if (match(p, last, s)) return p;
		first = ++p; // look at the next character
	}
}

struct Test
{
	string label;
	string op;
	string val;
	int res;
};

istream& operator>>(istream& is, Test& t)
{
	char a, b;

	if (is >> a >> t.label >> t.op >> b && (a != '{' || b != '{'))
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}
	if (!is) return is;

	char c;
	t.val = "";
	is >> c;
	while (c != '}')
	{
		t.val += c;
		is.get(c);
	}
	t.val.pop_back();

	char d;
	if (is >> t.res >> d && d != '}')
	{
		cerr << "ERROR: Invalid test file format" << '\n';
		return is;
	}

	return is;
}

string line_to_string(Document& d, int number)
{
	string line;
	if (number < 0 || d.lines.size() - 1 <= number) return line;
	auto p = d.lines.begin();
	my_advance(p, number);
	Line l = *p;
	for (auto ch : l) line += ch;
	line.pop_back();
	return line;
}

int test_all(istream& is, Document& d)
{
	int errors_num = 0;
	for (Test t; is >> t;)
	{
		if (t.op == "find")
		{
			auto p = find_text(d.begin(), d.end(), t.val);
			int actual_res = (p == d.end()) ? 0 : 1;

			if (actual_res != t.res)
			{
				cout << "failure: test " << t.label << " "
					<< t.op << "() val == " << t.val << "\n";
				++errors_num;
			}
		}
		if (t.op == "erase")
		{
			int n = stoi(t.val);
			string l = line_to_string(d, n);
			int before_size = d.lines.size();
			int actual_res = 0;
			erase_line(d, n);
			if (before_size != d.lines.size())
			{
				auto p = find_text(d.begin(), d.end(), l);
				if (p == d.end()) actual_res = 1;
			}
			if (actual_res != t.res)
			{
				cout << "failure: test " << t.label << " "
					<< t.op << "() val == " << t.val << "\n";
				++errors_num;
			}
		}
	}
	return errors_num;
}

int main()
{
	ifstream ifs{ "in.txt" };
	if (!ifs)
		throw exception("cannot open file");

	Document my_doc;
	ifs >> my_doc;
	print(my_doc);

	ifs.close();
	ifs.open("tests.txt");
	cout << "\nNumber of errors: " << test_all(ifs, my_doc) << "\n\n";

	print(my_doc);
}