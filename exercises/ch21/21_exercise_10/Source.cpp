#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
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

double price(double v, const Order& order)
{
	double order_price = 0;
	for (auto p : order.vp)
		order_price += p.unit_price * p.count;
	return v + order_price;
}

int main()
{
	vector<Order> vo;
	Order o;

	ifstream ifs{ "in.txt" };
	if (!ifs) throw exception("cannot read file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	
	while (ifs >> o)
		vo.push_back(o);

	ifstream ifs2{ "in2.txt" };
	if (!ifs2) throw exception("cannot read file");
	ifs2.exceptions(ifs2.exceptions() | ios_base::badbit);

	while (ifs2 >> o)
		vo.push_back(o);

	double total_value = 0;
	total_value = accumulate(vo.begin(), vo.end(), total_value, price);
	cout << "Total value of the orders: " << total_value << '\n';
}