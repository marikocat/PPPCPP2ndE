#include "MatrixIO.h"
#include <iostream>
using namespace Numeric_lib;

template<typename F, typename T>
auto my_apply(F f, const Matrix<T>& m)
{
	Matrix<decltype(f(m[0]))> mm(m.size());
	for (Index i = 0; i < m.size(); ++i) mm[i] = f(m[i]);
	return mm;
}

double triple(double d)
{
	return d * 3;
}

float triplef(float f)
{
	return f * 3;
}

int main()
{
	Matrix<int> mi(10);
	for (int i = 0; i < mi.size(); ++i)
		mi[i] = i + 1;
	std::cout << mi << '\n';

	Matrix<double> md = my_apply(triple, mi);
	std::cout << md << '\n';

	Matrix<float> mf = my_apply(triplef, md);
	std::cout << mf << '\n';
}