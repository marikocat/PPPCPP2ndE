#include <iostream>
#include <set>
using std::cout;
using std::ostream;
using std::set;
using std::string;

struct Fruit {
	string name;
	int count;
	double unit_price;

	Fruit(const string& n, int c = 1, double p = 0.0) : name(n), count(c), unit_price(p) {}
};

ostream& operator<<(ostream& os, const Fruit& f)
{
	os << f.name << ": " << f.count << " - " << f.unit_price;
	return os;
}

struct Fruit_order {
	bool operator()(const Fruit& a, const Fruit& b) const
	{
		return a.name < b.name;
	}
};

struct Fruit_comparison {
	bool operator()(const Fruit* p1, const Fruit* p2) const
	{
		return (*p1).name < (*p2).name;
	}
};

int main()
{
	set<Fruit*, Fruit_comparison> inventory;

	inventory.insert(new Fruit{ "quince", 5 });
	inventory.insert(new Fruit{ "apple", 200, 0.37 });

	for (auto p = inventory.begin(); p != inventory.end(); ++p)
		cout << **p << '\n';
	cout << '\n';

	for (const auto& x : inventory)
		cout << *x << '\n';
}