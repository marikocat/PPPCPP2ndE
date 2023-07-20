#include "MatrixIO.h"
using namespace Numeric_lib;

int main()
{
	Matrix<int> a(10);
	Matrix<int> b(100);
	Matrix<double> c(10);
	Matrix<int, 2> d(10, 10);
	Matrix<int, 3> e(10, 10, 10);

	std::cout << "sizeof(Matrix<int> a(10)): " << sizeof(a) << '\n';
	std::cout << "sizeof(Matrix<int> b(100)): " << sizeof(b) << '\n';
	std::cout << "sizeof(Matrix<double> c(10)): " << sizeof(c) << '\n';
	std::cout << "sizeof(Matrix<int, 2> d(10, 10)): " << sizeof(d) << '\n';
	std::cout << "sizeof(Matrix<int, 3> e(10, 10, 10)): " << sizeof(e) << '\n';
}