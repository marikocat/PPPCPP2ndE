#include <iostream>
#include "MatrixIO.h"
using namespace Numeric_lib;

int main()
{
	const int n = 10;
	Matrix<double> md(n);
	for (int i = 0; i < n;)
	{
		std::cin >> md[i];
		if (!std::cin)
		{
			std::cerr << "bad input\n";
			std::cin.clear();
			std::cin.ignore();
		}
		else i++;
	}

	std::cout << md << '\n';
}