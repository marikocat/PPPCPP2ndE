#include <iostream>
#include <list>
#include <vector>
#include <iterator>
using namespace std;

using Line = vector<char>;

class Text_iterator { // keep track of line and character position within a line
public:
	list<Line>::iterator ln;
	Line::iterator pos;

	using iterator_category = forward_iterator_tag;
	using value_type = char;
	using difference_type = size_t;
	using pointer = char*;
	using reference = char&;

	// start the iterator at line ll’s character position pp:
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
	--pos;
	return *this;
}

struct Document {
	list<Line> line;
	Document() { line.push_back(Line{}); } // Every Document starts out with a single empty line: 
	// Document’s constructor makes an empty line and pushes it into the list of lines.

	Text_iterator begin()
	{
		return Text_iterator(line.begin(), (*line.begin()).begin());
	}

	Text_iterator end()
	{
		auto last = line.end();
		--last;
		return Text_iterator(last, (*last).end());
	}
};

istream& operator>>(istream& is, Document& d)
{
	for (char ch; is.get(ch);)
	{
		d.line.back().push_back(ch); // add the character
		if (ch == '\n')
			d.line.push_back(Line{}); // add another line
	}
	if (d.line.back().size()) d.line.push_back(Line{}); // add final empty line
	return is;
}

void print(Document& d)
{
	for (auto p : d) cout << p;
}

void print2(Document& d)
{
	for (Text_iterator p = d.begin(); p != d.end(); ++p) cout << *p;
}

template<typename Iter>
void advance(Iter& p, int n)
{
	while (n > 0)
	{
		++p;
		--n;
	}
	while (n < 0)
	{
		--p;
		++n;
	}
}

void erase_line(Document& d, int n)
{
	if (n < 0 || n >= d.line.size() - 1) return;

	auto p = d.line.begin();
	advance(p, n);
	d.line.erase(p);
}

template<typename Iter>
bool match(Iter first, Iter last, const string& s)
{
	int i = 0;
	for (Iter p = first; p != last && i < s.size(); ++p, ++i)
		if (s[i] != *p) return false;
	return i == s.size();
}

Text_iterator find_txt(Text_iterator first, Text_iterator last, const string& s)
{
	if (s.size() == 0) return last;

	char first_char = s[0];
	while (true)
	{
		auto p = find(first, last, first_char);
		if (p == last || match(p, last, s)) return p;
		first = ++p;
	}
}

bool find_and_replace(Text_iterator first, Text_iterator last, const string& f, const string& r)
{
	auto p = find_txt(first, last, f);
	if (p == last) false;
	while (p != last)
	{
		for (char ch : f)
			p.pos = p.ln->erase(p.pos);
		p.pos = p.ln->insert(p.pos, r.begin(), r.end());
		p = find_txt(p, last, f);
	}
	return true;
}

int main()
{
	Document d;
	cin >> d;
	print(d);
	cout << '\n';
	print2(d);
	cout << '\n';
	erase_line(d, 1);
	print(d);
	cout << '\n';
	auto p = d.begin();
	++p; ++p; ++p;
	advance(p, -3);
	cout << *p << '\n';

	auto pp = find_txt(d.begin(), d.end(), "world\ntoday");
	if (pp == d.end())
		cout << "not found\n";
	else
		cout << "found\n";

	find_and_replace(d.begin(), d.end(), "nice", "fun");
	print(d);
}