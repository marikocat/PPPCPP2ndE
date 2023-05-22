#include<iostream>
using namespace std;

template<typename T>
class Number {
	T val;
public:
	Number() : val{ T() } {}
	explicit Number(T v) : val{ v } {}
	Number(const Number& n) : val{ n.val } {}
	Number(Number&& n) : val{ n.val } {}

	Number& operator=(const Number& n);
	Number& operator=(Number&& n);

	const T& get_val() const { return val; }
	void set_val(T v) { val = v; }
};

template<typename T>
Number<T>& Number<T>::operator=(const Number<T>& n)
{
	val = n.val;
	return *this;
}

template<typename T>
Number<T>& Number<T>::operator=(Number<T>&& n)
{
	val = n.val;
	return *this;
}

template<typename T>
Number<T> operator+(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() + n2.get_val()};
}

template<typename T>
Number<T> operator-(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() - n2.get_val()};
}

template<typename T>
Number<T> operator*(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() * n2.get_val()};
}

template<typename T>
Number<T> operator/(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() / n2.get_val()};
}

template<typename T>
Number<T> operator%(const Number<T>& n1, const Number<T>& n2)
{
	int res = int(n1.get_val()) % int(n2.get_val());
	return Number<T>{T(res)};
}

int modulo(double d1, double d2)
{
	return int(d1) % int(d2);
}

template<typename T>
ostream& operator<<(ostream& os, const Number<T>& n)
{
	os << n.get_val();
	return os;
}

template<typename T>
istream& operator>>(istream& is, Number<T>& n)
{
	T v;
	is >> v;
	if (!is) throw runtime_error("invalid input");
	n.set_x(v);
	return is;
}

template<typename T>
Number<T> f()
{
	return Number<T>{};
}

int main()
try
{
	Number<double> d1{ 10.0 };
	Number<double> d2{ 4.6 };
	cout << d1 + d2 << '\n';
	cout << d1 - d2 << '\n';
	cout << d1 * d2 << '\n';
	cout << d1 / d2 << '\n';
	cout << d1 % d2 << "\n\n";
	Number<double> d3{ d2 };
	Number<int> d4{ f<int>() };
	cout << d3 << ' ' << d4 << '\n';

	cout << "modulo: " << modulo(10.0, 3.2) << '\n';

	double d = 3.5;
	int x = d;
	cout << x << '\n';
}
catch (exception& e)
{
	cerr << "error: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}