#pragma once
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

istream& operator>>(istream& is, Purchase& p);
ostream& operator<<(ostream& os, const Purchase& p);

struct Order {
	string name;
	string address;
	vector<Purchase> vp;
};

istream& operator>>(istream& is, Order& o);
ostream& operator<<(ostream& os, const Order& o);

template<typename Iter>
void print_orders(Iter first, Iter last, ostream& os)
{
	while (first != last)
		os << *first++;
	os << "\n";
}

double price(double v, const Order& order);
double find_total_value(const string& filename);

void find_orders(const string& filename, const string& name, vector<Order>& orders)
{
	vector<Order> vo;
	Order o;

	ifstream ifs{ filename };
	if (!ifs) throw exception("cannot read file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	while (ifs >> o)
		vo.push_back(o);

	for (auto p = vo.begin(); p != vo.end();)
	{
		p = find_if(p, vo.end(), [&](const Order& order) {return name == order.name; });
		if (p != vo.end())
		{
			orders.push_back(*p);
			p++;
		}
	}
}

void get_orders_from_file(const string& filename, vector<Order>& orders)
{
	Order o;

	ifstream ifs{ filename };
	if (!ifs) throw exception("cannot read file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	while (ifs >> o)
		orders.push_back(o);
}