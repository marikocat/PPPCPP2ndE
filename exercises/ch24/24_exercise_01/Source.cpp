#include "MatrixIO.h"
using namespace Numeric_lib;

template<typename T>
void triple1(T& t) { t *= 3; }

template<typename T>
T triple2(const T& t) { return t * 3; }

template<typename T>
T triple(T& t) { return t *= 3; }

int main()
{
	Matrix<int> x(10);
	x = 7;

	for (int i = 0; i < x.dim1(); ++i) std::cout << x(i) << ' ';
	std::cout << '\n';

	x.apply(triple1<int>);
	for (int i = 0; i < x.dim1(); ++i) std::cout << x(i) << ' ';
	std::cout << '\n';

	Matrix<int> y = apply(triple2<int>, x);
	for (int i = 0; i < y.dim1(); ++i) std::cout << y(i) << ' ';
	std::cout << "\n\n";

	x = 7;
	y = 7;
	y = apply(triple<int>, x);
	x.apply(triple<int>);
	for (int i = 0; i < y.dim1(); ++i) std::cout << y(i) << ' ';
	std::cout << '\n';
	for (int i = 0; i < x.dim1(); ++i) std::cout << x(i) << ' ';
	std::cout << '\n';
}