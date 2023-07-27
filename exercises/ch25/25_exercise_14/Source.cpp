#include <vector>
#include <iostream>
using namespace std;

template<typename T, int N>
class Pool
{
	T p[N];
	bool used[N];
	int num_unused;
public:
	Pool() : p(), used(), num_unused(N) {}
	T* get();
	void free(T* obj);
	int available() const;
};

template<typename T, int N>
T* Pool<T, N>::get()
{
	for (int i = 0; i < N; ++i)
		if (!used[i])
		{
			used[i] = true;
			--num_unused;
			return &p[i];
		}
	return nullptr;
}

template<typename T, int N>
void Pool<T, N>::free(T* obj)
{
	*obj = T();
	++num_unused;
	used[obj - p] = false;
}

template<typename T, int N>
int Pool<T, N>::available() const
{
	return num_unused;
}

template<typename T, int N>
class Vector
{
	Pool<T, N> pool;
	T* data[N];
	int sz;
public:
	Vector();
	bool push_back(T el);
	T& operator[](int n);
	int size() const { return sz; }
};

template<typename T, int N>
Vector<T, N>::Vector() : pool(), data(), sz(0){}

template<typename T, int N>
bool Vector<T, N>::push_back(T el)
{
	if (data[sz] = pool.get())
	{
		(*this)[sz] = el;
		++sz;
		return true;
	}
	else
		return false;
}

template<typename T, int N>
T& Vector<T, N>::operator[](int n)
{
	return *data[n];
}

int main()
{
	Vector<int, 1000> v;
	try
	{
		for (int i = 0; i < 999; i++)
			v.push_back(i);
		cout << boolalpha << v.push_back(4999) << '\n';
		cout << boolalpha << v.push_back(5000) << '\n';
		cout << boolalpha << v.push_back(5001) << '\n';
		cout << v[999] << '\n';
	}
	catch (exception& e)
	{
		cerr << e.what() << '\n';
		exit(1);
	}
}