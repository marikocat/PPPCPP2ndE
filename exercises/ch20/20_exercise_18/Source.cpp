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
	Range_error() :out_of_range("Out of range") { }
};

// an almost real vector of Ts:
template<typename T, typename A = allocator<T>> class vector {
	A alloc; // use allocate to handle memory for elements
	int sz = 0; // the size
	T* elem = nullptr; // pointer to the elements (or 0)
	int space = 0; // number of elements plus number of free slots
public:
	class iterator;

	using size_type = unsigned long;
	using value_type = T;

	vector() {}
	explicit vector(int s) { resize(s); }

	vector(const vector&); // copy constructor
	vector& operator=(const vector&); // copy assignment

	~vector() { delete[] elem; } // destructor

	T& at(int n); // checked access
	const T& at(int n) const; // checked access

	T& operator[](int n); // unchecked access
	const T& operator[](int n) const; // unchecked access

	size_type size() const { return sz; }
	int capacity() const { return space; }

	void resize(int newsize, T val = T()); // growth
	void push_back(const T& val);
	void reserve(int newalloc);

	iterator begin() { return iterator{ elem, elem, elem + sz }; }
	iterator end() { return iterator{elem + sz, elem, elem + sz}; }

	iterator insert(iterator p, const T& val);
	iterator erase(iterator p);

	T& back() { return elem[sz - 1]; }
};

template<typename T, typename A>
class vector<T, A>::iterator {
	T* curr;
	T* first;
	T* last;
public:
	iterator(T* p, T* f, T* l) : curr{ p }, first{f}, last{l} {}

	iterator& operator++();
	iterator& operator--();
	iterator& operator+=(int n);
	iterator& operator-=(int n);
	iterator operator+(int n);
	iterator operator-(int n);
	int operator-(const iterator& b) const { return curr - b.curr; }
	T& operator*();
	T& operator[](int n);

	bool operator==(const iterator& b) const { return curr == b.curr; }
	bool operator!=(const iterator& b) const { return curr != b.curr; }
};

template<typename T, typename A>
typename vector<T, A>::iterator& vector<T, A>::iterator::operator++()
{
	++curr;
	if (curr < first || curr > last) throw Range_error();
	return *this;
}

template<typename T, typename A>
typename vector<T, A>::iterator& vector<T, A>::iterator::operator--()
{
	--curr;
	if (curr < first || curr > last) throw Range_error();
	return *this;
}

template<typename T, typename A>
typename vector<T, A>::iterator& vector<T, A>::iterator::operator+=(int n)
{
	curr += n;
	if (curr < first || curr > last) throw Range_error();
	return *this;
}

template<typename T, typename A>
typename vector<T, A>::iterator& vector<T, A>::iterator::operator-=(int n)
{
	curr -= n;
	if (curr < first || curr > last) throw Range_error();
	return *this;
}

template<typename T, typename A>
typename vector<T, A>::iterator vector<T, A>::iterator::operator+(int n)
{
	if (curr + n < first || curr + n > last) throw Range_error();
	return iterator{ curr + n, first, last };
}

template<typename T, typename A>
typename vector<T, A>::iterator vector<T, A>::iterator::operator-(int n)
{
	if (curr - n < first || curr - n > last) throw Range_error();
	return iterator{ curr - n, first, last };
}

template<typename T, typename A>
T& vector<T, A>::iterator::operator*()
{
	if (curr < first || curr >= last) throw Range_error();
	return *curr;
}

template<typename T, typename A>
T& vector<T, A>::iterator::operator[](int n)
{
	if (curr + n < first || curr + n >= last) throw Range_error();
	return *(curr + n);
}

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
	if (n < 0 || n >= sz) throw Range_error(n);
	return elem[n];
}

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw Range_error(n);
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
	for (int i = sz; i < newsize; ++i) alloc.construct(&elem[i], val);
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

template<typename T, typename A>
typename vector<T, A>::iterator vector<T, A>::insert(iterator p, const T& val)
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
typename vector<T, A>::iterator vector<T, A>::erase(iterator p)
{
	if (p == end()) return p;

	for (auto pos = p + 1; pos != end(); ++pos)
		*(pos - 1) = *pos;
	alloc.destroy(&*(end() - 1));
	--sz;
	return p;
}

template<typename Iterator, typename T>
Iterator find(Iterator start, Iterator end, const T& v)
{
	Iterator res = end;
	for (Iterator p = start; p != end; ++p)
		if (*p == v)
		{
			res = p;
			break;
		}
	return res;
}

template<typename T>
void print1(const vector<T>& v)
{
	for (int i = 0; i < v.size(); ++i)
		cout << v[i] << ' ';
	cout << '\n';
}

template<typename T>
void print2(vector<T>& v)
{
	for (T x : v)
		cout << x << ' ';
	cout << '\n';
}

int main()
{
	vector<int> v;
	v.resize(10, 1);

	v.resize(5);
	v.push_back(7);
	v.push_back(8);

	vector<int> v2;
	v2 = v;
	print1(v2);

	print2(v);

	vector<int>::iterator p = find(v.begin(), v.end(), 7);
	if (p == v.end()) cout << "not found\n";
	else cout << "7 at position: " << p - v.begin() << "\n";
	for (vector<int>::size_type i = 0; i < v.size(); ++i) cout << v[i] << ' ';
	cout << '\n';

	p = v.begin();
	++p; ++p; ++p; ++p; ++p;
	p = v.insert(p, 6);
	print2(v);

	p = v.erase(v.begin());
	print2(v);
}