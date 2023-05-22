#include <iostream>
using namespace std;

class Int {
	int x;
public:
	Int() : x{ 0 } {}
	explicit Int(int xx) : x{xx} {}
	Int(const Int& i) : x{ i.x } {}
	Int(Int&& i) : x{ i.x } {}

	Int& operator=(const Int& i);
	Int& operator=(Int&& i);

	int get_x() const { return x; }
	void set_x(int i) { x = i; }
};

Int& Int::operator=(const Int& i)
{
	x = i.x;
	return *this;
}

Int& Int::operator=(Int&& i)
{
	x = i.x;
	return *this;
}

Int operator+(const Int& i1, const Int& i2) { return Int{ i1.get_x() + i2.get_x() }; }
Int operator-(const Int& i1, const Int& i2) { return Int{ i1.get_x() - i2.get_x() }; }
Int operator*(const Int& i1, const Int& i2) { return Int{ i1.get_x() * i2.get_x() }; }
Int operator/(const Int& i1, const Int& i2) { return Int{ i1.get_x() / i2.get_x() }; }

ostream& operator<<(ostream& os, const Int& i)
{
	os << i.get_x();
	return os;
}

istream& operator>>(istream& is, Int& i)
{
	int n;
	is >> n;
	if (!is) throw runtime_error("invalid input");
	i.set_x(n);
	return is;
}

Int f() { return Int{ 7 }; }

int main()
{
	Int x1{ 5 };
	cout << x1 << '\n';
	Int x2{ x1 };
	cout << x2 << '\n';
	Int x3 = Int{ 3 };
	x3 = x2;
	cout << x3 << '\n';
	Int x4 = f();
	cout << x4 << '\n';

	Int x5;
	cin >> x5;
	cout << x5 << '\n';

	cout << x1 + x2 << '\n';
	cout << x4 - x1 << '\n';
	cout << x5 * x3 << '\n';
	cout << x5 / x2 << '\n';
}