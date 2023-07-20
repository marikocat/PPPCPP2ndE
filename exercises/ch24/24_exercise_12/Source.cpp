#include "MatrixIO.h"
#include <stdexcept>
using namespace Numeric_lib;

Matrix<double> operator*(Matrix<double, 2>& md, Matrix<double>& m)
{
	Matrix<double> res(md.dim1());

	for (int i = 0; i < md.dim1(); ++i)
	{
		res[i] = dot_product(md[i], m);
	}

	return res;
}

template<int N>
Matrix<double, N> operator+(Matrix<double, N>& m1, Matrix<double, N>& m2)
{
	if (m1.size() != m2.size()) throw std::exception("different dimensions");

	Matrix<double, N> res = m1;
	double* pres = res.data();
	double* pm2 = m2.data();
	for (int i = 0; i < res.size(); ++i)
		pres[i] += pm2[i];
	return res;
}

int main()
{
	double d1[][3] = {
		{1, 2, 3},
		{4, 5, 6}
	};
	double d2[] = { 10, 20, 30 };

	Matrix<double, 2> m1(d1);
	Matrix<double> m2(d2);
	Matrix<double> r = m1 * m2;
	std::cout << r << '\n';

	double d3[][4] = {
		{1, 1, 1, 1},
		{2, 2, 2, 2},
		{3, 3, 3, 3}
	};

	double d4[][4] = {
		{3, 3, 3, 3},
		{2, 2, 2, 2},
		{1, 1, 1, 1}
	};

	Matrix<double, 2> m3(d3);
	Matrix<double, 2> m4(d4);
	Matrix<double, 2> r2 = m3 + m4;
	std::cout << r2 << '\n';
}