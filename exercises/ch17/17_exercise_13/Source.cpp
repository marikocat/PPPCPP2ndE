#include <string>
#include <iostream>
using namespace std;

struct God {
	string name;
	string mythology;
	string vehicle;
	string weapon;
};

class Link {
	Link* prev;
	Link* succ;
public:
	God god;

	Link(const God& g, Link* p = nullptr, Link* s = nullptr)
		: god{ g }, prev{ p }, succ{ s } {}

	Link* insert(Link* n); // insert n before this object
	Link* add(Link* n); // insert n after this object
	Link* add_ordered(Link* n); // places element in its correct lexicographical position
	Link* erase(); // remove this object from list
	Link* find(const string& s); // find s in list
	Link* find_mythology(const string& s);
	const Link* find(const string& s) const; // find s in const list

	Link* advance(int n) const;

	Link* next() const { return succ; }
	Link* previous() const { return prev; }

	
};

Link* Link::insert(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = this;
	if (prev) prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

Link* Link::add(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	n->succ = succ;
	if (succ) succ->prev = n;
	n->prev = this;
	succ = n;
	return n;
}

Link* Link::add_ordered(Link* n)
{
	if (n == nullptr) return this;
	if (this == nullptr) return n;
	Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (n->god.name > p->god.name)
		{
			if (!p->succ) return p->add(n);
			p = p->succ;
		}
		else
		{
			return p->insert(n);
		}
	}
}

Link* Link::find(const string& s)
{
	if (this == nullptr) return this;
	Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

const Link* Link::find(const string& s) const
{
	if (this == nullptr) return this;
	const Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (p->god.name == s) return p;
		p = p->succ;
	}
	return nullptr;
}

Link* Link::find_mythology(const string& s)
{
	if (this == nullptr) return this;
	Link* p = this;
	while (p)
	{
		if (p->god.mythology == s) return const_cast<Link*>(p);
		p = p->succ;
	}
	return nullptr;
}

Link* Link::erase()
{
	if (this == nullptr) return nullptr;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

Link* Link::advance(int n) const
{
	if (this == nullptr) return nullptr;
	const Link* p = this;
	if (n > 0)
	{
		while (n--) {
			if (p->succ == nullptr) return nullptr;
			p = p->succ;
		}
	}
	else if (n < 0)
	{
		while (n++)
		{
			if (p->prev == nullptr) return nullptr;
			p = p->prev;
		}
	}
	return const_cast<Link*>(p);
}

void print_all(Link* p)
{
	while (p->previous()) p = p->previous();
	while (p)
	{
		cout << "{ ";
		cout << p->god.name << ", " << p->god.mythology << ", " << p->god.vehicle << ", " << p->god.weapon << " }";
		if (p = p->next()) cout << "\n";
	}
	cout << "\n";
}

int main()
{
	Link* gods = new Link{ {"Thor", "Norse", "Crows", "Ax"} };
	gods = gods->insert(new Link{ {"Odin", "Norse", "Horse called Sleipner", "Spear called Gungnir"} });
	gods = gods->insert(new Link{ {"Zeus", "Greek", "", "lightning"} });
	gods = gods->insert(new Link{ {"Freia", "Norse", "Air", "Magic"} });
	gods = gods->insert(new Link{ {"Athena", "Greek", "Chariot", "Sword" } });
	gods = gods->insert(new Link{ {"Mars", "Roman", "Chariot", "Spear" } });
	gods = gods->insert(new Link{ {"Poseidon", "Greek", "", "Trident" } });
	gods = gods->insert(new Link{ {"Hera", "Greek", "Horse", "Sword" } });
	gods = gods->insert(new Link{ {"Jupiter", "Roman", "Horse", "Thunder" } });
	gods = gods->insert(new Link{ {"Appolo", "Roman", "Chariot", "Spear" } });

	Link* temp = gods->find_mythology("Norse");

	Link* norse_gods = new Link{ temp->god };
	while (temp = temp->next()->find_mythology("Norse"))
	{
		norse_gods->add_ordered(new Link{ temp->god });
	}
	print_all(norse_gods);
	cout << "\n";

	temp = gods->find_mythology("Greek");

	Link* greek_gods = new Link{ temp->god };
	while (temp = temp->next()->find_mythology("Greek"))
	{
		greek_gods->add_ordered(new Link{ temp->god });
	}
	print_all(greek_gods);
	cout << "\n";

	temp = gods->find_mythology("Roman");

	Link* roman_gods = new Link{ temp->god };
	while (temp = temp->next()->find_mythology("Roman"))
	{
		roman_gods->add_ordered(new Link{ temp->god });
	}
	print_all(roman_gods);
	cout << "\n";
}