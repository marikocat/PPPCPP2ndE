#include "MatrixIO.h"
#include <stdexcept>
using namespace Numeric_lib;

int main()
{
	std::cout << "enter n and m: ";
	int n, m;
	std::cin >> n >> m;

	if (!std::cin) throw std::exception("Bad input");

	Matrix<int, 2> mi(n, m);

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= m; ++j)
		{
			mi(i - 1, j - 1) = i * j;
		}
	std::cout << mi << '\n';
}