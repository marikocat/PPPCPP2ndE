#include <iostream>
#include <vector>
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

template<typename T, typename U>
Number<T> operator*(const Number<T>& n1, const Number<U>& n2)
{
	return Number<T>{n1.get_val()* T(n2.get_val())};
}

template<typename T>
Number<T> operator/(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() / n2.get_val()};
}

template<typename T>
Number<T> operator%(const Number<T>& n1, const Number<T>& n2)
{
	return Number<T>{n1.get_val() % n2.get_val()};
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

template<typename T, typename U>
T f(const vector<T>& vt, const vector<U>& vu)
{
	T sum = T();
	for (int i = 0; i < vt.size() && i < vu.size(); ++i)
		sum = sum + vt[i] * vu[i];
	return sum;
}

int main()
try
{
	vector<Number<double>> vd{ Number<double>{1.1}, Number<double>{2.2}, Number<double>{3.3} };
	vector<Number<int>> vi{ Number<int>{10}, Number<int>{20}, Number<int>{30} };

	cout << f(vd, vi) << '\n';
	cout << f(vi, vd) << '\n';
}
catch (exception& e)
{
	cerr << "error: " << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}