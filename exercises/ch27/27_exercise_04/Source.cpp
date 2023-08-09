#include <iostream>
using namespace std;

template<typename T>
struct Link
{
	Link* pre;
	Link* suc;
	T val;

	Link(T t = T{}) : val{ t }, pre{ 0 }, suc{ 0 } {}
};

template<typename T>
class List
{
	Link<T>* first;
	Link<T>* last;
public:
	List() : first{ 0 }, last{ 0 }{};
	~List();

	void push_back(Link<T>* p);
	void push_front(Link<T>* p);

	void insert(Link<T>* p, Link<T>* q); // insert q before p
	Link<T>* erase(Link<T>* p); // remove p from list

	Link<T>* advance(Link<T>* p, int n);
	Link<T>* get_first() const { return first; }
	Link<T>* get_last() const { return last; }
};

template<typename T>
List<T>::~List()
{
	Link<T>* curr = first;
	while (curr)
	{
		Link<T>* next = curr->suc;
		delete curr;
		curr = next;
	}
}

template<typename T>
void List<T>::push_back(Link<T>* p)
{
	if (!p) return;

	if (last)
	{
		last->suc = p;
		p->pre = last;
	}
	else
	{
		first = p;
	}
	last = p;
}

template<typename T>
void List<T>::push_front(Link<T>* p)
{
	if (!p) return;

	if (first)
	{
		first->pre = p;
		p->suc = first;
	}
	else
	{
		last = p;
	}
	first = p;
}

template<typename T>
void List<T>::insert(Link<T>* p, Link<T>* q)
{
	if (!p || !q)
		return;

	if (p->pre)
	{
		q->suc = p;
		q->pre = p->pre;
		p->pre->suc = q;
		p->pre = q;
	}
	else
	{
		q->suc = p;
		p->pre = q;
		first = q;
	}
}

template<typename T>
Link<T>* List<T>::erase(Link<T>* p)
{
	if (!p)
	{
		cerr << "cannot erase\n";
		return 0;
	}

	if (p == first)
	{
		if (p->suc)
		{
			first = p->suc;
			p->suc->pre = 0;
			return first;
		}
		else
		{
			first = last = 0;
			return 0;
		}
	}
	else if (p == last)
	{
		if (p->pre)
		{
			last = p->pre;
			p->pre->suc = 0;
			return 0;
		}
		else
		{
			first = last = 0;
			return 0;
		}
	}
	else
	{
		p->suc->pre = p->pre;
		p->pre->suc = p->suc;
		return p->suc;
	}
}

template<typename T>
Link<T>* List<T>::advance(Link<T>* p, int n)
{
	if (!p)
	{
		cerr << "cannot andance\n";
		return 0;
	}

	if (n > 0)
	{
		while (n > 0)
		{
			if (p->suc)
			{
				p = p->suc;
			}
			else
			{
				return 0;
			}
			n--;
		}
	}
	else
	{
		while (n < 0)
		{
			if (p->pre)
			{
				p = p->pre;
			}
			else
			{
				return 0;
			}
			n++;
		}
	}
	return p;
}

int main()
{
	List<string> lst;

	lst.push_back(new Link<string>{ "Norah" });
	lst.push_back(new Link<string>{ "Annemarie" });
	lst.push_back(new Link<string>{ "Kris" });

	lst.erase(lst.advance(lst.get_first(), 1));

	int count = 0;
	for (Link<string>* curr = lst.get_first(); curr; curr = curr->suc)
	{
		count++;
		cout << "element " << count << ": " << curr->val << "\n";
	}
	cout << endl;

	lst.push_front(new Link<string>{ "Kate" });

	count = 0;
	for (Link<string>* curr = lst.get_first(); curr; curr = curr->suc)
	{
		count++;
		cout << "element " << count << ": " << curr->val << "\n";
	}
	cout << endl;

	lst.insert(lst.advance(lst.get_first(), 2), new Link<string>{ "Lea" });

	count = 0;
	for (Link<string>* curr = lst.get_first(); curr; curr = curr->suc)
	{
		count++;
		cout << "element " << count << ": " << curr->val << "\n";
	}
	cout << endl;
}