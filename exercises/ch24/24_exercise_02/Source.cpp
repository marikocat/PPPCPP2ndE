#include "MatrixIO.h"
using namespace Numeric_lib;

template<class T>
struct Triple1
{
	void operator()(T& t) { t *= 3; }
};

template<class T>
void triple1(T& t) { t *= 3; }

template<class T>
struct Triple2
{
	T operator()(const T& t) { return t * 3; }
};

template<class T>
T triple2(const T& t) { return t * 3; }

template<class T>
struct Triple
{
	T operator()(T& t) { return t *= 3; }
};

template<class T>
T triple(T& t) { return t *= 3; }

int main()
{
	Matrix<int> x(10);
	x = 7;

	std::cout << x << '\n';

	x.apply(Triple1<int>());
	std::cout << x << '\n';

	Matrix<int> y = apply(Triple2<int>(), x);
	std::cout << y << "\n\n";

	x = 7;
	y = 7;
	y = apply(Triple<int>(), x);
	x.apply(Triple<int>());
	std::cout << y << '\n';
	std::cout << x << '\n';
}