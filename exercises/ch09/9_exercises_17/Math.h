#pragma once
#include "..\std_lib_facilities.h"

namespace Math {
	int greatest_common_divisor(int a, int b);

	class Rational {
		int numerator;
		int denumerator;

		void normalize();
		void reduce();
	public:
		class ZeroDenumerator {};
		Rational(int n, int d);
		Rational(int n);
		Rational();

		double convert_to_double() const;
		int get_numerator() const { return numerator; }
		int get_denumerator() const { return denumerator; }
	};

	Rational operator+(const Rational& r1, const Rational& r2);
	Rational operator-(const Rational& r1, const Rational& r2);
	Rational operator*(const Rational& r1, const Rational& r2);
	Rational operator/(const Rational& r1, const Rational& r2);
	bool operator==(const Rational& r1, const Rational& r2);
	ostream& operator<<(ostream& os, const Rational& r);
	istream& operator>>(istream& is, Rational& r);
}