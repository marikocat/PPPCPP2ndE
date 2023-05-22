#include <iostream>
using namespace std;

template<typename T>
class my_unique_ptr {
	T* ptr;
public:
	my_unique_ptr(T* p) : ptr{ p } {}
	~my_unique_ptr() { delete ptr; }

	T* release();

	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }
};

struct X {
	int x;
};

template<typename T>
T* my_unique_ptr<T>::release()
{
	T* temp = ptr;
	ptr = nullptr;
	return temp;
}

int main()
{
	my_unique_ptr<double> p{ new double{10} };
	*p = 20;
	cout << *p << '\n';

	my_unique_ptr<X> p2{ new X{15} };
	cout << p2->x << '\n';
	(*p2).x = 30;
	cout << (*p2).x << '\n';

	my_unique_ptr<X> p3{ p2.release() };
	cout << p3->x << '\n';
}