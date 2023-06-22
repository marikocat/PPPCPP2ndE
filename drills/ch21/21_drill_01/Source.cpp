#include <algorithm>
#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

struct Item {
	string name;
	int id;
	double value;
};

ostream& operator<<(ostream& os, const Item& i)
{
	os << "(\"" << i.name << "\", " << i.id << ", " << i.value << ")\n";
	return os;
}

void fill_from_file(vector<Item>& vi, const string& file_name)
{
	ifstream ifs{ file_name };
	if (!ifs) throw exception("cannot open file");

	char ch1, ch2;
	string s;
	int i;
	double d;
	while (ifs >> ch1 >> s >> i >> d >> ch2)
	{
		if (ch1 != '{' || ch2 != '}') throw exception("invalid input");
		Item item{ s, i, d };
		vi.push_back(item);
	}
	if (!ifs && !ifs.eof()) throw exception("cannot read the file");
}

void fill_from_file(list<Item>& li, const string& file_name)
{
	ifstream ifs{ file_name };
	if (!ifs) throw exception("cannot open file");

	char ch1, ch2;
	string s;
	int i;
	double d;
	while (ifs >> ch1 >> s >> i >> d >> ch2)
	{
		if (ch1 != '{' || ch2 != '}') throw exception("invalid input");
		Item item{ s, i, d };
		li.push_back(item);
	}
	if (!ifs && !ifs.eof()) throw exception("cannot read the file");
}

struct Cmp_by_name {
	bool operator()(const Item& a, const Item& b) const
	{
		return a.name < b.name;
	}
};

struct Cmp_by_id {
	bool operator()(const Item& a, const Item& b) const
	{
		return a.id < b.id;
	}
};

struct Cmp_by_value_decr {
	bool operator()(const Item& a, const Item& b) const
	{
		return a.value > b.value;
	}
};

int main()
{
	vector<Item> v;
	fill_from_file(v, "in.txt");
	for (Item i : v)
		cout << i;
	sort(v.begin(), v.end(), Cmp_by_name());
	cout << endl;
	for (Item i : v)
		cout << i;
	sort(v.begin(), v.end(), Cmp_by_id());
	cout << endl;
	for (Item i : v)
		cout << i;
	sort(v.begin(), v.end(), Cmp_by_value_decr());
	cout << endl;
	for (Item i : v)
		cout << i;
	v.insert(v.end(), Item{ "horse shoe", 99, 12.34 });
	v.insert(v.end(), Item{ "Canon S400", 9988, 499.95 });
	cout << endl;
	for (Item i : v)
		cout << i;

	v.erase(find_if(v.begin(), v.end(), 
		[](const Item& i) {return i.name == "pad"; }));
	v.erase(find_if(v.begin(), v.end(),
		[](const Item& i) {return i.name == "ball"; }));
	sort(v.begin(), v.end(), Cmp_by_name());
	cout << endl;
	for (Item i : v)
		cout << i;

	cout << "\nFill list with Items\n";
	list<Item> li;
	fill_from_file(li, "in.txt");
	for (Item i : li)
		cout << i;
	li.sort(Cmp_by_name());
	cout << endl;
	for (Item i : li)
		cout << i;
	li.sort(Cmp_by_id());
	cout << endl;
	for (Item i : li)
		cout << i;
	li.sort(Cmp_by_value_decr());
	cout << endl;
	for (Item i : li)
		cout << i;
	li.insert(li.end(), Item{ "horse shoe", 99, 12.34 });
	li.insert(li.end(), Item{ "Canon S400", 9988, 499.95 });
	cout << endl;
	for (Item i : li)
		cout << i;

	li.erase(find_if(li.begin(), li.end(),
		[](const Item& i) {return i.name == "pad"; }));
	li.erase(find_if(li.begin(), li.end(),
		[](const Item& i) {return i.name == "ball"; }));
	li.sort(Cmp_by_name());
	cout << endl;
	for (Item i : li)
		cout << i;
}