#include <iostream>
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

template<typename T, typename A = allocator<T*>>
class pvector {
	A alloc;
	int sz = 0;
	T** elem = nullptr;
	int space = 0;
public:
	pvector() {}
	explicit pvector(int s) { resize(s); }

	~pvector(); // destructor

	pvector(const pvector&); // copy constructor
	pvector& operator=(const pvector&); // copy assignment

	T* at(int n); // checked access
	const T* at(int n) const; // checked access

	T* operator[](int n) { return elem[n]; }
	const T* operator[](int n) const { return elem[n]; }

	int size() const { return sz; }
	int capacity() const { return space; }

	void reserve(int newalloc);
	void resize(int newsize, T* valp = nullptr);
	void push_back(const T& val);
	void push_back(T* valp);
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
T* pvector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A>
const T* pvector<T, A>::at(int n) const
{
	if (n < 0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A> void pvector<T, A>::resize(int newsize, T* valp)
{
	reserve(newsize);
	for (int i = sz; i < newsize; ++i)
	{
		alloc.construct(&elem[i], valp);
	}
	for (int i = newsize; i < sz; ++i)
	{
		delete elem[i];
		alloc.destroy(&elem[i]);
	}
	sz = newsize;
}

template<typename T, typename A>
void pvector<T, A>::reserve(int newalloc)
{
	if (newalloc <= space) return; // never decrease allocation
	T** p = alloc.allocate(newalloc);
	for (int i = 0; i < sz; ++i)
	{
		alloc.construct(&p[i], elem[i]); // copy
	}
	for (int i = 0; i < sz; ++i)
	{
		delete elem[i];
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
	alloc.construct(&elem[sz], new T{ val });
	++sz; // increase the size (sz is the number of elements)
}

template<typename T, typename A>
void pvector<T, A>::push_back(T* valp)
{
	if (space == 0)
		reserve(8); // start with space for 8 elements
	else if (sz == space)
		reserve(2 * space); // get more space
	alloc.construct(&elem[sz], valp);
	++sz; // increase the size (sz is the number of elements)
}

template<typename T, typename A>
void print(const pvector<T, A>& v)
{
	for (int i = 0; i < v.size(); ++i)
		if (v[i])
			cout << *v[i] << ' ';
		else
			cout << "_ ";
	cout << '\n';
}

int main()
{
	pvector<int> pv;
	pv.resize(10);
	int x = 1;
	int* px = new int{ 5 };
	pv.push_back(x);
	pv.push_back(px);

	print(pv);
}