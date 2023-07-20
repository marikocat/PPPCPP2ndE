#include "MatrixIO.h"
using namespace Numeric_lib;

int main()
{
	Matrix<int> a(10);
	Matrix<int> b(100);
	Matrix<double> c(10);
	Matrix<int, 2> d(10, 10);
	Matrix<int, 3> e(10, 10, 10);

	std::cout << "number of elements in a: " << a.size() << '\n';
	std::cout << "number of elements in b: " << b.size() << '\n';
	std::cout << "number of elements in c: " << c.size() << '\n';
	std::cout << "number of elements in d: " << d.size() << '\n';
	std::cout << "number of elements in e: " << e.size() << '\n';
}