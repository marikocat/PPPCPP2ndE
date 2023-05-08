#include <string>
#include <iostream>
using namespace std;

class Link {
	Link* succ;
public:
	string value;

	Link(const string& v, Link* s = nullptr)
		: value{ v }, succ{ s } {}

	Link* insert(Link* n); // insert n before this object
	Link* add(Link* n); // insert n after this object
	Link* erase(); // remove this object from list
	Link* find(const string& s); // find s in list
	const Link* find(const string& s) const;

	Link* advance(int n) const;

	Link* next() const { return succ; }
};

Link* Link::insert(Link* n) // insert n before this object; return n
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;
	return n;
}

Link* Link::add(Link* n) // insert n after this object
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = succ;
	succ = n;
	return n;
}

Link* Link::find(const string& s)
{
	if (this == nullptr) return this;
	Link* p = this;
	while (p)
	{
		if (p->value == s) return p;
		p = p->succ;
	}
	return nullptr;
}

const Link* Link::find(const string& s) const
{
	if (this == nullptr) return this;
	const Link* p = this;
	while (p)
	{
		if (p->value == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link* Link::erase() // remove this object from list
{
	if (this == nullptr) return this;
	Link* temp = new Link{value};
	if (succ)
	{
		value = succ->value;
		succ = succ->succ;
	}
	return temp;
}

Link* Link::advance(int n) const
{
	if (this == nullptr) return nullptr;
	const Link* p = this;
	if (n > 0)
	{
		while (n--) {
			if (succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	return const_cast<Link*>(p);
}

void print_all(Link* p)
{
	cout << "{ ";
	while (p)
	{
		cout << p->value;
		if (p = p->next()) cout << ", ";
	}
	cout << " }";
}

int main()
{
	Link* norse_gods = new Link{ "Thor" };
	norse_gods = norse_gods->insert(new Link{ "Odin" });
	norse_gods = norse_gods->insert(new Link{ "Zeus" });
	norse_gods = norse_gods->insert(new Link{ "Freia" });

	Link* greek_gods = new Link{ "Hera" };
	greek_gods = greek_gods->insert(new Link{ "Athena" });
	greek_gods = greek_gods->insert(new Link{ "Mars" });
	greek_gods = greek_gods->insert(new Link{ "Poseidon" });

	Link* p = greek_gods->find("Mars");
	if (p) p->value = "Ares";

	Link* p2 = norse_gods->find("Zeus");
	if (p2)
	{
		if (p2 == norse_gods) norse_gods = p2->next();
		p2 = p2->erase();
		greek_gods = greek_gods->insert(p2);
	}

	print_all(norse_gods);
	cout << "\n";
	print_all(greek_gods);
	cout << "\n";
}