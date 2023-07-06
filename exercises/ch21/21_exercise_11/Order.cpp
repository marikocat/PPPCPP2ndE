#include "Order.h"

istream& operator>>(istream& is, Purchase& p)
{
	char ch1, ch2;
	string n;
	double d;
	int c;
	if (is >> ch1 >> n >> d >> c >> ch2)
	{
		if (ch1 != '{' || ch2 != '}') throw exception("invalid input");
		p = Purchase{ n, d, c };
	}
	if (!is && !is.eof()) throw exception("cannot read input");
	return is;
}

ostream& operator<<(ostream& os, const Purchase& p)
{
	os << "{" << p.name << ": " << p.unit_price << " " << p.count << "}";
	return os;
}

istream& operator>>(istream& is, Order& o)
{
	const char eol = '\n';

	string n;
	string a;
	vector<Purchase> vp;

	getline(is, n);
	getline(is, a);

	if (is.eof()) return is;
	if (!is) throw exception("cannot read input for order");

	char ch = is.get();
	while (ch != eol && !is.eof())
	{
		if (ch == '{')
		{
			is.putback(ch);
			Purchase p;
			is >> p;
			vp.push_back(p);
		}
		else
		{
			is.putback(ch);
			break;
		}
		ch = is.get();
	}

	if (is.eof())
	{
		is.clear();
	}

	o = Order{ n, a, vp };
	return is;
}

ostream& operator<<(ostream& os, const Order& o)
{
	os << o.name << "\n";
	os << o.address << "\n";
	for (auto p : o.vp)
		os << p;
	os << "\n";
	return os;
}