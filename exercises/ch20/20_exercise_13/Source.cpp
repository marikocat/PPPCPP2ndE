#include <exception>
#include <iostream>
using std::cin;
using std::cout;
using std::exception;

template<typename Elem>
class list {
	// representation and implementation details
public:
	struct Link;
	class iterator; // member type: iterator

	list() : first{ nullptr } {}
	~list();

	iterator begin(); // iterator to first element
	iterator end(); // iterator to one beyong last element

	iterator insert(iterator p, const Elem& v); // insert v into list before p
	iterator erase(iterator p); // erase p from the list

	void push_back(const Elem& v); // insert v at end
	void push_front(const Elem& v); // insert v at front
	void pop_front(); // remove the first element
	void pop_back(); // remove the last element

	Elem& front(); // the first element
	Elem& back(); // the last element

	Link* first;
	// Link* last;
};

template<typename Elem>
struct list<Elem>::Link {
	Link* prev;
	Link* succ;
	Elem val;
	Link(const Elem& v = Elem(), Link* p = 0, Link* s = 0) : val{ v }, prev{ p }, succ{ s }{}
};

template<typename Elem> // requires Element<Elem>()
class list<Elem>::iterator {
public:
	Link* curr; // current link

	iterator(Link* p) : curr{ p } {}

	iterator& operator++() { curr = curr->succ; return *this; } // forward
	iterator& operator--() { curr = curr->prev; return *this; } // backward
	Elem& operator*() { return curr->val; }

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }
};

template<typename Elem>
list<Elem>::~list()
{
	auto p = first;
	if (p)
	{
		while (p->succ)
		{
			auto temp = p;
			p = p->succ;
			delete temp;
		}
		delete p;
	}
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::begin()
{
	return iterator(first);
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::end()
{
	return iterator(nullptr);
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::insert(iterator p, const Elem& v)
{
	Link* lp = new Link();
	lp->val = v;
	if (!first)
		first = lp;
	else
	{
		lp->succ = p.curr;
		lp->prev = p.curr->prev;
		if (p.curr->prev)
		{
			p.curr->prev->succ = lp;
		}
		else
			first = lp;
		p.curr->prev = lp;
	}
	return iterator{ lp };
}

template<typename Elem>
typename list<Elem>::iterator list<Elem>::erase(iterator p)
{
	if (!p.curr) throw exception("cannot erase from empty list");

	Link* lp = p.curr->succ;
	if (lp)
		lp->prev = p.curr->prev;
	if (p.curr->prev)
	{
		p.curr->prev->succ = lp;
	}
	else
		first = lp;
	delete p.curr;
	return iterator{ lp };
}

template<typename Elem>
void list<Elem>::push_front(const Elem& v)
{
	insert(first, v);
}

template<typename Elem>
void list<Elem>::push_back(const Elem& v)
{
	Link* lp = new Link(v);
	if (!first)
	{
		first = lp;
		return;
	}
	Link* p = first;
	while (p->succ) p = p->succ;
	p->succ = lp;
	lp->prev = p;
}

template<typename Elem>
void list<Elem>::pop_front()
{
	if (!first) return;
	erase(iterator(first));
}

template<typename Elem>
void list<Elem>::pop_back()
{
	if (!first) return;
	Link* p = first;
	while (p->succ) p = p->succ;
	erase(iterator(p));
}

template<typename Elem>
Elem& list<Elem>::front()
{
	if (!first) throw exception("there is no front element in empty list");
	return first->val;
}

template<typename Elem>
Elem& list<Elem>::back()
{
	if (!first) throw exception("there is no back element in empty list");
	Link* p = first;
	while (p->succ) p = p->succ;
	return p->val;
}

template<typename Iterator> // requires Input_iterator<Iter>()
Iterator high(Iterator first, Iterator last)
// return an iterator to the element in[first, last) that has the highest value
{
	Iterator high = first;
	for (Iterator p = first; p != last; ++p)
		if (*high < *p) high = p;
	return high;
}

void f()
{
	list<int> lst;
	for (int x; cin >> x;) lst.push_front(x);
	list<int>::iterator p = high(lst.begin(), lst.end());
	if (p == lst.end())
		cout << "The list is empty\n";
	else
		cout << "The highest value is " << *p << '\n';
	p = lst.begin();
	for (; p != lst.end(); ++p)
		cout << *p << ' ';
	cout << '\n';
	p = lst.begin();
	++p; ++p;
	lst.erase(p);
	p = lst.begin();
	for (; p != lst.end(); ++p)
		cout << *p << ' ';
	cout << '\n';
	cout << "front element: " << lst.front() << '\n';
	cout << "back element: " << lst.back() << '\n';
	lst.pop_front();
	lst.pop_back();
	for (auto el : lst) cout << el << ' ';
	cout << '\n';
	lst.push_back(60);
	lst.push_back(70);
	for (auto el : lst) cout << el << ' ';
	cout << '\n';
	lst.push_front(60);
	lst.push_front(70);
	for (auto el : lst) cout << el << ' ';
	cout << '\n';
}

int main()
{
	f();
}