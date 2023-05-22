#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class counted_ptr {
	T* ptr;
	int* use_count;
public:
	counted_ptr(const T& t) : ptr{ new T{t} }, use_count{ new int{1} } {}
	counted_ptr(const counted_ptr&);
	~counted_ptr();

	counted_ptr& operator=(const counted_ptr&);
	T* operator->() { return ptr; }
	T& operator*() { return *ptr; }

	int get_count() const { return *use_count; }
};

template<typename T>
counted_ptr<T>::counted_ptr(const counted_ptr& a)
	: ptr{a.ptr}, use_count{a.use_count}
{
	++* use_count;
	cout << "copy constructor: " << *use_count << '\n';
}

template<typename T>
counted_ptr<T>::~counted_ptr()
{
	cout << "counted_ptr destructor called\n";
	if (use_count)
		if (*use_count == 1)
		{
			cout << "deleting ptr\n";
			delete ptr;
			delete use_count;
		}
		else
		{
			cout << "detract 1 from " << * use_count << '\n';
			ptr = nullptr;
			--* use_count;
		}
}

template<typename T>
counted_ptr<T>& counted_ptr<T>::operator=(const counted_ptr& a)
{
	ptr = a.ptr;
	use_count = a.use_count;
	++* use_count;
}

struct X {
	int x;
};

ostream& operator<<(ostream& os, const X& ob)
{
	cout << ob.x;
	return os;
}

template<typename T>
void f(const counted_ptr<T>& p)
{
	counted_ptr<T> temp{ p };
	cout << p.get_count() << '\n';
	cout << *temp << '\n';
}

int main()
{
	counted_ptr<X> px{ X{15} };
	counted_ptr<X> px2{ px };
	counted_ptr<X> px3{ px2 };
	cout << px.get_count() << ' ' << px2.get_count() << ' ' << px3.get_count() << '\n';
	f(px3);
	cout << "returned from f()\n\n";

	vector<counted_ptr<X>> v;
	v.push_back(px);
	cout << px.get_count() << "\n\n";
	v.push_back(px2);
	cout << px2.get_count() << "\n\n";
	v.push_back(px3);
	cout << px3.get_count() << "\n\n";

	for (int i = 0; i < v.size(); ++i)
		cout << *v[i] << ' ';
	cout << '\n';
}