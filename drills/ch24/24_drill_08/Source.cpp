#include "MatrixIO.h"
#include <limits>
using namespace Numeric_lib;

int main()
{
	Matrix<int, 2> m(2, 3);
	int* p = m.data();
	for (int i = 0; i < m.size(); ++i)
	{
		int n;
		while (!(std::cin >> n))
		{
			std::cerr << "bad input: enter integer number\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		p[i] = n;
	}

	std::cout << m << '\n';
}