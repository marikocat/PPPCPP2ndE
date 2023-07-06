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