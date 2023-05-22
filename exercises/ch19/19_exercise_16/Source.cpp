#include <iostream>
#include <memory>
#include <stdexcept>
using std::cout;
using std::cin;
using std::out_of_range;
using std::allocator;

struct Range_error : out_of_range { // enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error"), index(i) { }
};

template<typename T, typename A>
struct Representation {
	A alloc; // use allocate to handle memory for elements
	int sz = 0; // the size
	T* elem = nullptr; // pointer to the elements (or 0)
	int space = 0; // number of elements plus number of free slots

	~Representation() { delete[] elem; }
};

// an almost real vector of Ts:
template<typename T, typename A = allocator<T>> class vector {
	Representation<T, A>* r;
public:
	vector() : r{ new Representation<T, A>() } {}
	explicit vector(int s) { resize(s); }

	vector(const vector&); // copy constructor
	vector& operator=(const vector&); // copy assignment

	~vector() { delete r; } // destructor

	T& at(int n); // checked access
	const T& at(int n) const; // checked access

	T& operator[](int n); // unchecked access
	const T& operator[](int n) const; // unchecked access

	int size() const { return r->sz; }
	int capacity() const { return r->space; }

	void resize(int newsize, T val = T()); // growth
	void push_back(const T& val);
	void reserve(int newalloc);
};

template<typename T, typename A>
vector<T, A>::vector(const vector& a)
{
	resize(a.r->sz);
	for (int i = 0; i < r->sz; ++i)
		r->alloc.construct(&r->elem[i], a[i]);
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>& a)
{
	if (this == &a) return *this;

	resize(a.r->sz);
	for (int i = 0; i < r->sz; ++i)
		r->alloc.construct(&r->elem[i], a[i]);
	return *this;
}

template<typename T, typename A>
const T& vector<T, A>::at(int n) const
{
	if (n < 0 || n >= r->sz) throw Range_error(n);
	return r->elem[n];
}

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= r->sz) throw Range_error(n);
	return r->elem[n];
}

template<typename T, typename A>
const T& vector<T, A>::operator[](int n) const
{
	return r->elem[n];
}

template<typename T, typename A>
T& vector<T, A>::operator[](int n)
{
	return r->elem[n];
}

template<typename T, typename A> void vector<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = 0; i < newsize; ++i) r->alloc.construct(&r->elem[i], val);
	for (int i = newsize; i < r->sz; ++i) r->alloc.destroy(&r->elem[i]);
	r->sz = newsize;
}

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= r->space) return; // never decrease allocation
	T* p = r->alloc.allocate(newalloc);
	for (int i = 0; i < r->sz; ++i)
	{
		r->alloc.construct(&p[i], r->elem[i]); // copy
	}
	for (int i = 0; i < r->sz; ++i)
	{
		r->alloc.destroy(&r->elem[i]); // destroy
	}
	r->alloc.deallocate(r->elem, r->space); // deallocate old space
	r->elem = p;
	r->space = newalloc;
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val)
{
	if (r->space == 0)
		reserve(8); // start with space for 8 elements
	else if (r->sz == r->space)
		reserve(2 * r->space); // get more space
	r->alloc.construct(&r->elem[r->sz], val); // add val at end
	++r->sz; // increase the size (sz is the number of elements)
}

struct No_default {
	int i;
	No_default(int n) :i{ n } {}
};

void print_some(vector<int>& v)
{
	int i = -1;
	while (cin >> i && i != -1)
		try
	{
		cout << "v[" << i << "] == " << v.at(i) << "\n";
	}
	catch (Range_error)
	{
		cout << "bad index: " << i << "\n";
	}
}

int main()
{
	vector<int> v;
	cout << sizeof(v) << '\n';
	v.resize(10, 1);
	print_some(v);
	v.resize(5);
	v.push_back(7);
	v.push_back(8);
	print_some(v);
	vector<int> v2;
	v2 = v;
	for (int i = 0; i < v2.size(); ++i)
		cout << v2[i] << ' ';
	cout << '\n';
}