#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;

template<typename T> class allocator {
public:
	T* allocate(int n);
	void deallocate(T* p, int n);

	void construct(T* p, const T& v);
	void destroy(T* p);
};

template<typename T>
T* allocator<T>::allocate(int n)
{
	T* p = (T*)malloc(sizeof(T) * n);
	return p;
}

template<typename T>
void allocator<T>::deallocate(T* p, int n)
{
	free(p);
}

template<typename T>
void allocator<T>::construct(T* p, const T& v)
{
	new(p) T{ v };
}

template<typename T>
void allocator<T>::destroy(T* p)
{
	p->~T();
}

struct out_of_range_exc {

};

// an almost real vector of Ts:
template<typename T, typename A = allocator<T>> class vector {
	A alloc; // use allocate to handle memory for elements
	int sz = 0; // the size
	T* elem = nullptr; // pointer to the elements (or 0)
	int space = 0; // number of elements plus number of free slots
public:
	vector() {}
	explicit vector(int s) { resize(s); }

	vector(const vector&); // copy constructor
	vector& operator=(const vector&); // copy assignment

	~vector() { delete[] elem; } // destructor

	T& at(int n); // checked access
	const T& at(int n) const; // checked access

	T& operator[](int n); // unchecked access
	const T& operator[](int n) const; // unchecked access

	int size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T()); // growth
	void push_back(const T& val);
	void reserve(int newalloc);
};

template<typename T, typename A>
vector<T, A>::vector(const vector& a)
{
	resize(a.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elem[i], a[i]);
}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>& a)
{
	if (this == &a) return *this;

	resize(a.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elem[i], a[i]);
	return *this;
}

template<typename T, typename A>
const T& vector<T, A>::at(int n) const
{
	if (n < 0 || n >= sz) throw out_of_range_exc();
	return elem[n];
}

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw out_of_range_exc();
	return elem[n];
}

template<typename T, typename A>
const T& vector<T, A>::operator[](int n) const
{
	return elem[n];
}

template<typename T, typename A>
T& vector<T, A>::operator[](int n)
{
	return elem[n];
}

template<typename T, typename A> void vector<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = 0; i < newsize; ++i) alloc.construct(&elem[i], val);
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
	sz = newsize;
}

template<typename T, typename A>
void vector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return; // never decrease allocation
	T* p = alloc.allocate(newalloc);
	for (int i = 0; i < sz; ++i)
	{
		alloc.construct(&p[i], elem[i]); // copy
	}
	for (int i = 0; i < sz; ++i)
	{
		alloc.destroy(&elem[i]); // destroy
	}
	alloc.deallocate(elem, space); // deallocate old space
	elem = p;
	space = newalloc;
}

template<typename T, typename A>
void vector<T, A>::push_back(const T& val)
{
	if (space == 0)
		reserve(8); // start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); // get more space
	alloc.construct(&elem[sz], val); // add val at end
	++sz; // increase the size (sz is the number of elements)
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
	catch (out_of_range_exc)
	{
		cout << "bad index: " << i << "\n";
	}
}

int main()
{
	vector<int> v;
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