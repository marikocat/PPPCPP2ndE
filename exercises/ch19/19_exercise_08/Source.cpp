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
	int sz; // the size
	T* elem; // pointer to the elements (or 0)
	int space; // number of elements plus number of free slots
public:
	vector() :sz{ 0 }, elem{ nullptr }, space{ 0 } {}
	explicit vector(int s) : sz{ s }, elem{ new T[s] }, space{ s }
	{
		for (int i = 0; i < sz; ++i) elem[i] = 0; // elements are initialized
	}

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
vector<T, A>::vector(const vector&)
{

}

template<typename T, typename A>
vector<T, A>& vector<T, A>::operator=(const vector<T, A>&)
{

}

template<typename T, typename A>
T& vector<T, A>::at(int n)
{
	if (n < 0 || n >= sz) throw out_of_range_exc();
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
	cout << "reserve: allocate\n";
	T* p = alloc.allocate(newalloc);
	for (int i = 0; i < sz; ++i)
	{
		cout << "reserve: construct\n";
		alloc.construct(&p[i], elem[i]); // copy
	}
	for (int i = 0; i < sz; ++i)
	{
		cout << "reserve: destroy\n";
		alloc.destroy(&elem[i]); // destroy
	}
	alloc.deallocate(elem, space); // deallocate old space
	elem = p;
	space = newalloc;
	// We move an element to the new space by constructing a copy in uninitialized space and then destroying the original. 
	// We can’t use assignment because for types such as string, assignment assumes that the target area has been initialized.
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
	//vector<double> v1;
	//v1.resize(10);
	//for (int i = 0; i < 10; ++i) cout << v1[i] << ' ';
	//cout << endl;
	//v1.resize(20, 0.0);
	//for (int i = 0; i < 20; ++i) cout << v1[i] << ' ';
	//cout << endl;
	//v1.resize(30, 1.0);
	//for (int i = 0; i < 30; ++i) cout << v1[i] << ' ';
	//cout << endl;

	////vector<No_default> v2(10); // error: tries to make 10 No_default()s
	//vector<No_default> v3;
	//v3.resize(100, No_default(2)); // add 100 copies of No_default(2)
	//for (int i = 0; i < 10; ++i) cout << v3[i].i << ' ';
	//cout << endl;
	//// v3.resize(200); // error: tries to add 100 No_default()s
}