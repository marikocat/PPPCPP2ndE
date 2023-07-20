#include "MatrixIO.h"
#include <string>
#include <exception>
using namespace Numeric_lib;

typedef Numeric_lib::Matrix<double, 2> Matrixx;
typedef Numeric_lib::Matrix<double, 1> Vector;

struct Elim_failure : std::domain_error {
	Elim_failure(std::string s) : std::domain_error(s) { }
};

struct Back_subst_failure : std::domain_error {
	Back_subst_failure(std::string s) : std::domain_error(s) { }
};

void classical_elimination(Matrixx& A, Vector& b)
{
	const Index n = A.dim1();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Index j = 0; j < n - 1; ++j)
	{
		const double pivot = A(j, j);
		if (pivot == 0) throw Elim_failure("Elimination failure in row " + std::to_string(j));

		// fill zeros into each element under the diagonal of the ith row:
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j); // make the corresponding change to b
		}
	}
}

void elim_with_partial_pivot(Matrixx& A, Vector& b)
{
	const Index n = A.dim1();

	for (Index j = 0; j < n; ++j)
	{
		Index pivot_row = j;

		// look for a suitable pivot:
		for (Index k = j + 1; k < n; ++k)
			if (std::abs(A(k, j)) > abs(A(pivot_row, j))) pivot_row = k;

		//swap the rows if we found a better pivot:
		if (pivot_row != j)
		{
			A.swap_rows(j, pivot_row);
			std::swap(b(j), b(pivot_row));
		}

		//elimination:
		for (Index i = j + 1; i < n; ++i)
		{
			const double pivot = A(j, j);
			if (pivot == 0) throw std::exception("can't solve: pivot==0");
			const double mult = A(i, j) / pivot;
			A[i].slice(j) = scale_and_add(A[j].slice(j), -mult, A[i].slice(j));
			b(i) -= mult * b(j);
		}
	}
}

Vector back_substitution(const Matrixx& A, const Vector& b)
{
	const Index n = A.dim1();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i)
	{
		double s = b(i) - dot_product(A[i].slice(i + 1), x.slice(i + 1));

		if (double m = A(i, i))
			x(i) = s / m;
		else
			throw Back_subst_failure("Back substitution failure in row " + std::to_string(i));
	}
	return x;
}

Vector classical_gaussian_elimination(Matrixx A, Vector b)
{
	classical_elimination(A, b);
	return back_substitution(A, b);
}

Vector pivotal_elimination(Matrixx A, Vector b)
{
	elim_with_partial_pivot(A, b);
	return back_substitution(A, b);
}

int main()
try
{
	double a[2][2] = {
		{0, 1},
		{1, 0}
	};

	double b[2] = { 5, 6 };

	Matrixx A(a);
	Vector B(b);

	std::cout << "Solving A*x=B" << std::endl;
	std::cout << "A=\n" << A << std::endl;
	std::cout << "B=" << B << std::endl;

	//Vector x1 = classical_gaussian_elimination(A, B);
	//std::cout << "x1=" << x1 << std::endl;
	Vector x = pivotal_elimination(A, B);
	std::cout << "x=" << x << std::endl;
}
catch (std::exception& e)
{
	std::cerr << "error: " << e.what() << '\n';
}
catch (...)
{
	std::cerr << "Oops: unknown exception!\n";
}