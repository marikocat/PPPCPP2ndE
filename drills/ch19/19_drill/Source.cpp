#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct S {
	S(T v) : val{ v } {}

	const T& get() const;
	T& get();
	void set(const T& v);

	S& operator=(const T&);
private:
	T val;
};

template<typename T> 
const T& S<T>::get() const
{
	return val;
}

template<typename T>
T& S<T>::get()
{
	return val;
}

template<typename T> 
void S<T>::set(const T& v)
{
	val = v;
}

template<typename T> 
S<T>& S<T>::operator=(const T& v)
{
	val = v;
	return *this;
}

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
	v.clear();
	char ch1, ch2;
	is >> ch1;
	if (ch1 != '{') throw runtime_error("invalid input, should start with {");
	while (is >> ch2 && ch2 != '}')
	{
		if (ch2 != ',') cin.putback(ch2);
		T val;
		is >> val;
		if (!is) throw runtime_error("invalid input, wrong value");
		v.push_back(val);
	}
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	os << "{ ";
	for (int i = 0; i < v.size(); ++i)
	{
		os << v[i];
		if (i < v.size() - 1)
			os << ", ";
	}
	os << " }";
	return os;
}

template<typename T>
void read_val(T& v)
{
	cout << "Enter value: ";
	cin >> v;
	if (!cin)
	{
		if (cin.eof()) return;
		throw runtime_error("invalid input");
	}
}

int main()
try
{
	S<int> i{ 10 };
	S<char> ch{ 'A' };
	S<double> d{ 1.5 };
	S<string> s{ "hello" };
	S<vector<int>> v{ vector<int>{1, 2, 3, 4, 5} };
	cout << i.get() << '\n'
		<< ch.get() << '\n'
		<< d.get() << '\n'
		<< s.get() << '\n';
	for (int num : v.get()) cout << num << ' ';
	cout << '\n';

	i.set(20);
	cout << i.get() << '\n';
	v.set(vector<int>{1, 2, 3});
	for (int num : v.get()) cout << num << ' ';
	cout << '\n';

	i = 30;
	cout << i.get() << '\n';
	v = vector<int>{ 1, 2, 3, 4, 5 };
	for (int num : v.get()) cout << num << ' ';
	cout << '\n';

	d.get() = 10.0;
	cout << d.get() << '\n';

	read_val(i.get());
	cout << i.get() << '\n';

	read_val(ch.get());
	cout << ch.get() << '\n';

	read_val(d.get());
	cout << d.get() << '\n';

	read_val(s.get());
	cout << s.get() << '\n';

	read_val(v.get());
	cout << v.get() << '\n';
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}