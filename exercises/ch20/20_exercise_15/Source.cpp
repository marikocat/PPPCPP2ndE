#include <iostream>
#include <cstdlib>
#include <stdexcept>
using std::cout;
using std::cin;
using std::out_of_range;

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

struct Range_error : out_of_range { // enhanced vector range error reporting
	int index;
	Range_error(int i) :out_of_range("Range error"), index(i) { }
};

// an almost real vector of Ts:
template<typename T, typename A = allocator<T>> class pvector {
	A alloc; // use allocate to handle memory for elements
	int sz = 0; // the size
	T* elem = nullptr; // pointer to the elements (or 0)
	int space = 0; // number of elements plus number of free slots
public:
	using size_type = unsigned long;
	using value_type = T;
	using iterator = T*;
	using const_iterator = const T*;

	pvector() {}
	explicit pvector(int s) { resize(s); }

	~pvector(); // destructor

	pvector(const pvector&); // copy constructor
	pvector& operator=(const pvector&); // copy assignment

	T& at(int n); // checked access
	const T& at(int n) const; // checked access

	T& operator[](int n); // unchecked access
	const T& operator[](int n) const; // unchecked access

	size_type size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T()); // growth
	void push_back(const T& val);
	void reserve(int newalloc);

	iterator begin() { return elem; }
	const_iterator begin() const { return elem; }
	iterator end() { return elem + sz; }
	const_iterator end() const { return elem + sz; }

	iterator insert(iterator p, const T& val);
	iterator erase(iterator p);

	T& back() { return elem[sz - 1]; }
};

template<typename T, typename A>
pvector<T, A>::~pvector()
{
	for (int i = 0; i < sz; ++i)
		delete elem[i];
	delete[] elem;
}

template<typename T, typename A>
pvector<T, A>::pvector(const pvector& a)
{
	resize(a.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elem[i], a[i]);
}

template<typename T, typename A>
pvector<T, A>& pvector<T, A>::operator=(const pvector<T, A>& a)
{
	if (this == &a) return *this;

	resize(a.sz);
	for (int i = 0; i < sz; ++i)
		alloc.construct(&elem[i], a[i]);
	return *this;
}

template<typename T, typename A>
const T& pvector<T, A>::at(int n) const
{
	if (n < 0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A>
T& pvector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A>
const T& pvector<T, A>::operator[](int n) const
{
	return elem[n];
}

template<typename T, typename A>
T& pvector<T, A>::operator[](int n)
{
	return elem[n];
}

template<typename T, typename A> void pvector<T, A>::resize(int newsize, T val)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val);
	for (int i = newsize; i < sz; ++i) alloc.destroy(&elem[i]);
	sz = newsize;
}

template<typename T, typename A>
void pvector<T, A>::reserve(int newalloc)
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
void pvector<T, A>::push_back(const T& val)
{
	if (space == 0)
		reserve(8); // start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); // get more space
	alloc.construct(&elem[sz], val); // add val at end
	++sz; // increase the size (sz is the number of elements)
}

template<typename T, typename A>
typename pvector<T, A>::iterator pvector<T, A>::insert(iterator p, const T& val)
{
	int index = p - begin();
	if (size() == capacity())
		reserve(size() == 0 ? 8 : 2 * size());

	alloc.construct(elem + sz, back());

	++sz;
	iterator pp = begin() + index;
	for (auto pos = end() - 2; pos != pp; --pos)
		*pos = *(pos - 1);
	*(begin() + index) = val;
	return pp;
}

template<typename T, typename A>
typename pvector<T, A>::iterator pvector<T, A>::erase(iterator p)
{
	if (p == end()) return p;

	for (auto pos = p + 1; pos != end(); ++pos)
		*(pos - 1) = *pos;
	alloc.destroy(&*(end() - 1));
	--sz;
	return p;
}

template<typename T, typename A>
void print(const pvector<T, A>& v)
{
	for (auto x : v)
		if (x)
			cout << *x << ' ';
		else
			cout << "_ ";
	cout << '\n';
}

int main()
{
	pvector<int*> pv;
	pv.resize(10);
	print(pv);
	pv.push_back(new int{ 5 });
	pv.push_back(new int{ 6 });
	pv.push_back(new int{ 7 });
	print(pv);
	pv.erase(pv.begin());
	print(pv);
	pv.push_back(new int{ 8 });
	pv.push_back(new int{ 9 });
	pv.push_back(new int{ 10 });
	print(pv);
	pv.at(2) = new int{ 3 };
	print(pv);
}