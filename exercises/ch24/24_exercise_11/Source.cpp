#include "MatrixIO.h"
using namespace Numeric_lib;

int f(int& i) { return i *= i; }
int f2(int& i, int b) { return i *= b; }

template<typename T>
void swap_columns(Matrix<T, 2>& m, int n, int k)
{
	for (int i = 0; i < m.dim1(); ++i)
		std::swap(m[i][n], m[i][k]);
}

int main()
{
	Matrix<int, 2> a(3, 4);

	Matrix<int, 2> a2 = a;
	a = a2;
	a[0] = 7;
	a[1] = 8;
	a[2] = 9;
	a.swap_rows(1, 2);
	std::cout << a << '\n';

	for (int i = 0; i < a.dim1(); ++i)
		for (int j = 0; j < a.dim2(); ++j)
		{
			a[i][j] = 7 + j;
		}

	std::cout << a << '\n';
	swap_columns(a, 2, 3);
	std::cout << a << '\n';
}