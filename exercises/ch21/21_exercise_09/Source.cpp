#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
#include <string>
using namespace std;

struct Purchase {
	string name;
	double unit_price;
	int count;
};

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

struct Order {
	string name;
	string address;
	vector<Purchase> vp;
};

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

template<typename Iter>
void print_orders(Iter first, Iter last, ostream& os)
{
	while (first != last)
		os << *first++;
	os << "\n";
}

int main()
{
	vector<Order> vo;
	ifstream ifs{ "in.txt" };
	if (!ifs) throw exception("cannot read file");

	Order o;
	while (ifs >> o)
		vo.push_back(o);
	if (ifs.eof()) cout << "end of file\n";

	print_orders(vo.begin(), vo.end(), cout);

	sort(vo.begin(), vo.end(), [](const Order& o1, const Order& o2) {return o1.name < o2.name; });

	print_orders(vo.begin(), vo.end(), cout);

	list<Order> lo;
	ifstream ifs2{ "in2.txt" };
	if (!ifs2) throw exception("cannot read file2");

	while (ifs2 >> o)
		lo.push_back(o);
	if (ifs.eof()) cout << "end of file2\n";

	print_orders(lo.begin(), lo.end(), cout);

	lo.sort([](const Order& o1, const Order& o2) {return o1.address < o2.address; });

	print_orders(lo.begin(), lo.end(), cout);

	ofstream ofs{ "out.txt" };
	if (!ofs) throw exception("cannot write to a file");

	print_orders(vo.begin(), vo.end(), ofs);
	ofs.close();
	ofs.open("out2.txt");
	print_orders(lo.begin(), lo.end(), ofs);

	ifs.close();
	ifs.open("out.txt");

	ifs2.close();
	ifs2.open("out2.txt");

	ofs.close();
	ofs.open("out3.txt");

	istream_iterator<Order> iifs{ ifs };
	istream_iterator<Order> iifs2{ ifs2 };
	istream_iterator<Order> eos;
	ostream_iterator<Order> oofs{ ofs };

	merge(iifs, eos, iifs2, eos, oofs,
		[](const Order& o1, const Order& o2) -> bool {return o1.name < o2.name; });
}