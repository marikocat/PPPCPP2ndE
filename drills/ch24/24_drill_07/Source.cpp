#include <complex>
#include <iostream>
#include "MatrixIO.h"
using namespace Numeric_lib;

using cmplx = std::complex<double>;

int main()
{
	const int n = 10;
	Matrix<cmplx> m(n);
	for (int i = 0; i < n;)
	{
		std::cin >> m(i);
		if (!std::cin)
		{
			std::cerr << "bad input\n";
			std::cin.clear();
			std::cin.ignore();
		}
		else ++i;
	}
	cmplx sum;
	for (int i = 0; i < m.size(); ++i)
		sum += m[i];

	std::cout << sum << '\n';
}