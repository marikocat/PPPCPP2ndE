#include <iostream>
#include <exception>

template<typename Elem>
class slist {
public:
	struct Link;
	class iterator;

	slist() : first{ nullptr } {}
	~slist();

	iterator begin() { return iterator{ first }; }
	iterator end() { return iterator{ nullptr }; }

	iterator insert(iterator p, const Elem& v); // insert v into list AFTER p
	iterator erase(iterator p); // erase p from the list

	void push_back(const Elem& v);
	void push_front(const Elem& v);
	void pop_front();
	void pop_back();

	Elem& front();
	Elem& back();

	Link* first;
};

template<typename Elem>
struct slist<Elem>::Link {
	Elem val;
	Link* next;
	Link(Elem v = Elem(), Link* n = nullptr) : val{ v }, next{ n } {}
};

template<typename Elem>
class slist<Elem>::iterator {
public:
	Link* curr;

	iterator(Link* p) : curr{p} {}

	iterator& operator++() { curr = curr->next; return *this; }
	Elem& operator*() { return curr->val; }

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }
};

template<typename Elem>
slist<Elem>::~slist()
{
	auto p = first;
	while (p->next)
	{
		auto temp = p;
		p = p->next;
		delete temp;
	}
	delete p;
}

template<typename Elem>
typename slist<Elem>::iterator slist<Elem>::insert(iterator p, const Elem& v)
{
	Link* lp = new Link{ v };

	if (!first)
		first = lp;
	else
	{
		lp->next = p.curr;
		Link* prev = first;
		while (prev->next)
		{
			if (prev->next == p.curr)
			{
				prev->next = lp;
				break;
			}
			prev = prev->next;
		}
		if (p.curr == first)
			first = lp;
	}
	return iterator{ lp };
}

template<typename Elem>
typename slist<Elem>::iterator slist<Elem>::erase(iterator p)
{
	if (!p.curr) throw std::exception("cannot erase from empty list");

	Link* lp = p.curr->next;
	if (p.curr == first)
	{
		first = lp;
	}
	else
	{
		Link* prev = first;
		while (prev->next)
		{
			if (prev->next == p.curr)
			{
				prev->next = lp;
				break;
			}
			prev = prev->next;
		}
	}
	delete p.curr;
	return iterator{ lp };
}

template<typename Elem>
void slist<Elem>::push_back(const Elem& v)
{
	Link* lp = new Link{ v };
	if (!first)
	{
		first = lp;
		return;
	}
	Link* prev = first;
	while (prev->next) prev = prev->next;
	prev->next = lp;
}

template<typename Elem>
void slist<Elem>::push_front(const Elem& v)
{
	insert(iterator{ first }, v);
}

template<typename Elem>
void slist<Elem>::pop_back()
{
	if (!first) return;

	Link* p = first;
	while (p->next) p = p->next;
	erase(iterator(p));
}

template<typename Elem>
void slist<Elem>::pop_front()
{
	if (!first) return;
	erase(iterator{ first });
}

template<typename Elem>
Elem& slist<Elem>::front()
{
	if (!first) throw std::exception("no front element in empty list");
	return first->val;
}

template<typename Elem>
Elem& slist<Elem>::back()
{
	if (!first) throw std::exception("no back element in empty list");
	Link* p = first;
	while (p->next) p = p->next;
	return p->val;
}

int main()
{
	slist<int> lst;
	for (int x; std::cin >> x;) lst.push_front(x);
	for (auto el : lst) std::cout << el << ' ';
	std::cout << '\n';


	slist<int>::iterator p = lst.begin();
	++p; ++p;
	p = lst.erase(p);
	++p;
	lst.erase(p);
	for (auto el : lst) std::cout << el << ' ';
	std::cout << '\n';

	std::cout << "front element: " << lst.front() << '\n';
	std::cout << "back element: " << lst.back() << '\n';
	lst.pop_front();
	lst.pop_back();
	for (auto el : lst) std::cout << el << ' ';
	std::cout << '\n';
	lst.push_back(60);
	lst.push_back(70);
	for (auto el : lst) std::cout << el << ' ';
	std::cout << '\n';
	lst.push_front(60);
	lst.push_front(70);
	for (auto el : lst) std::cout << el << ' ';
	std::cout << '\n';
}