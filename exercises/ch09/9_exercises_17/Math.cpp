#include "Math.h"

namespace Math {
	// helper function
	int greatest_common_divisor(int a, int b)
	{
		a = abs(a);
		b = abs(b);

		if (b > a) swap(a, b);

		while (b != 0)
		{
			int temp{ b };
			b = a % b;
			a = temp;
		}

		return a;
	}

	// Rational class interface
	Rational::Rational(int n, int d)
		: numerator{n}, denumerator{d}
	{
		if (d == 0) throw ZeroDenumerator{};
		normalize();
		reduce();
	}

	Rational::Rational(int n)
		: numerator{ n }, denumerator{ 1 }
	{

	}

	Rational::Rational()
		: numerator{ 0 }, denumerator{ 1 }
	{

	}

	double Rational::convert_to_double() const
	{
		return double(numerator) / denumerator;
	}

	// Rational class private functions
	void Rational::normalize()
	{
		if (denumerator < 0)
		{
			denumerator = -denumerator;
			numerator = -numerator;
		}
	}

	void Rational::reduce()
	{
		int gcd{ greatest_common_divisor(numerator, denumerator) };
		numerator /= gcd;
		denumerator /= gcd;
	}

	// Rational class operators
	Rational operator+(const Rational& r1, const Rational& r2)
	{
		int numer{ r1.get_numerator() * r2.get_denumerator() + r2.get_numerator() * r1.get_denumerator() };
		int denumer{ r1.get_denumerator() * r2.get_denumerator() };
		return Rational(numer, denumer);
	}

	Rational operator-(const Rational& r1, const Rational& r2)
	{
		int numer{ r1.get_numerator() * r2.get_denumerator() - r2.get_numerator() * r1.get_denumerator() };
		int denumer{ r1.get_denumerator() * r2.get_denumerator() };
		return Rational(numer, denumer);
	}

	Rational operator*(const Rational& r1, const Rational& r2)
	{
		int numer{ r1.get_numerator() * r2.get_numerator() };
		int denumer{ r1.get_denumerator() * r2.get_denumerator() };
		return Rational(numer, denumer);
	}

	Rational operator/(const Rational& r1, const Rational& r2)
	{
		if (r2.get_numerator() == 0) throw Rational::ZeroDenumerator{};

		int numer{ r1.get_numerator() * r2.get_denumerator() };
		int denumer{ r1.get_denumerator() * r2.get_numerator() };
		return Rational{ numer, denumer };
	}

	bool operator==(const Rational& r1, const Rational& r2)
	{
		return ((r1.get_numerator() * r2.get_denumerator()) == (r1.get_denumerator() * r2.get_numerator()));
	}

	ostream& operator<<(ostream& os, const Rational& r)
	{
		os << r.get_numerator() << "/" << r.get_denumerator();
		return os;
	}

	istream& operator>>(istream& is, Rational& r)
	{
		int n, d;
		char c;
		is >> n >> c >> d;
		if (!is) return is;
		if (c != '/')
		{
			is.clear(ios_base::failbit);
			return is;
		}
		r = Rational{ n, d };

		return is;
	}
}