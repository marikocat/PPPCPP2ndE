#include <iostream>
using namespace std;

struct God {
	string name;
	string mythology;
	string vehicle;
	string weapon;

	God(const string& n, const string& m = "", const string& v = "", const string& w = "")
		: name{ n }, mythology{ m }, vehicle{ v }, weapon{ w } {}
};

bool operator>(const God& g1, const God& g2)
{
	return g1.name > g2.name;
}

bool operator==(const God& g1, const God& g2)
{
	return g1.name == g2.name;
}

ostream& operator<<(ostream& os, const God& g)
{
	os << "{ ";
	os << g.name << ", " << g.mythology << ", " << g.vehicle << ", " << g.weapon;
	os << " }";
	return os;
}

template<typename T>
class Link {
	Link* prev;
	Link* succ;
public:
	T val;

	Link(const T& v, Link* p = nullptr, Link* s = nullptr)
		: val{ v }, prev{ p }, succ{ s } {}

	Link* insert(Link* n);
	Link* add(Link* n);
	Link* add_ordered(Link* n);
	Link* erase();
	Link* find(const T& t);
	const Link* find(const T& t) const;

	Link* advance(int n) const;

	Link* next() const { return succ; }
	Link* previous() const { return prev; }
};

template<typename T>
Link<T>* Link<T>::insert(Link<T>* n) // insert n before this object
{
	if (!n) return this;
	if (!this) return n;
	n->succ = this;
	if (prev) prev->succ = n;
	n->prev = prev;
	prev = n;
	return n;
}

template<typename T>
Link<T>* Link<T>::add(Link<T>* n) // insert n after this object
{
	if (!n) return this;
	if (!this) return n;
	n->succ = succ;
	if (succ) succ->prev = n;
	n->prev = this;
	succ = n;
	return n;
}

template<typename T>
Link<T>* Link<T>::add_ordered(Link<T>* n) // places element in its correct lexicographical position
{
	if (!n) return this;
	if (!this) return n;
	Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (n->val > p->val)
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

template<typename T>
Link<T>* Link<T>::find(const T& t) // find t in list
{
	if (!this) return this;
	Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (p->val == t) return p;
		p = p->succ;
	}
	return nullptr;
}

template<typename T>
const Link<T>* Link<T>::find(const T& t) const // find t in const list
{
	if (!this) return this;
	const Link* p = this;
	while (p->prev) p = p->prev;
	while (p)
	{
		if (p->val == t) return p;
		p = p->succ;
	}
	return nullptr;
}

template<typename T>
Link<T>* Link<T>::erase() // remove this object from list
{
	if (!this) return this;
	if (succ) succ->prev = prev;
	if (prev) prev->succ = succ;
	return succ;
}

template<typename T>
Link<T>* Link<T>::advance(int n) const
{
	if (!this) return this;
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

template<typename T>
void print_all(Link<T>* p)
{
	while (p->previous()) p = p->previous();
	while (p)
	{
		cout << p->val << "\n";
		p = p->next();
	}
	cout << "\n";
}

template<typename T>
void delete_all(Link<T>* p)
{
	if (!p) return;
	while (p->previous()) p = p->previous();
	while (p->next())
	{
		p = p->next();
		delete p->previous();
	}
	delete p;
}

int main()
try
{
	Link<God>* gods = new Link<God>{ {"Thor", "Norse", "Crows", "Ax"} };
	gods = gods->insert(new Link<God>{ {"Odin", "Norse", "Horse called Sleipner", "Spear called Gungnir"} });
	gods = gods->insert(new Link<God>{ {"Zeus", "Greek", "", "lightning"} });
	gods = gods->insert(new Link<God>{ {"Freia", "Norse", "Air", "Magic"} });
	gods = gods->insert(new Link<God>{ {"Athena", "Greek", "Chariot", "Sword" } });
	gods = gods->insert(new Link<God>{ {"Mars", "Roman", "Chariot", "Spear" } });
	gods = gods->insert(new Link<God>{ {"Poseidon", "Greek", "", "Trident" } });
	gods = gods->insert(new Link<God>{ {"Hera", "Greek", "Horse", "Sword" } });
	gods = gods->insert(new Link<God>{ {"Jupiter", "Roman", "Horse", "Thunder" } });
	gods = gods->insert(new Link<God>{ {"Appolo", "Roman", "Chariot", "Spear" } });

	Link<God>* norse_gods = new Link<God>{ (*gods->find(God{"Odin"})).val };
	norse_gods->add_ordered(new Link<God>{ (*gods->find(God{"Freia"})).val });
	norse_gods->add_ordered(new Link<God>{ (*gods->find(God{"Thor"})).val });

	Link<God>* greek_gods = new Link<God>{ (*gods->find(God{"Zeus"})).val };
	greek_gods->add_ordered(new Link<God>{ (*gods->find(God{"Athena"})).val });
	greek_gods->add_ordered(new Link<God>{ (*gods->find(God{"Poseidon"})).val });
	greek_gods->add_ordered(new Link<God>{ (*gods->find(God{"Hera"})).val });

	Link<God>* roman_gods = new Link<God>{ (*gods->find(God{"Appolo"})).val };
	roman_gods->add_ordered(new Link<God>{ (*gods->find(God{"Mars"})).val });
	roman_gods->add_ordered(new Link<God>{ (*gods->find(God{"Jupiter"})).val });

	print_all(norse_gods);
	print_all(greek_gods);
	print_all(roman_gods);

	delete_all(norse_gods);
	delete_all(greek_gods);
	delete_all(roman_gods);
}
catch (exception& e)
{
	cerr << "error: " << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}