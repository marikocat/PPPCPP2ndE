#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>
using namespace std;

typedef vector<double> Vector;
typedef vector<vector<double>> Matrixx;
typedef long Index;

ostream& operator<<(ostream& os, const Vector& v)
{
	os << "{ ";
	for (const auto& el : v)
		os << el << ' ';
	os << "}";
	return os;
}

ostream& operator<<(ostream& os, const Matrixx& m)
{
	os << "{\n";
	for (const auto& el : m)
		cout << el << '\n';
	os << "}";
	return os;
}

void animated_print(const Matrixx& m, const Vector& v)
{
	cout << "A and B:\n";
	for (int i = 0; i < m.size(); ++i)
	{
		cout << m[i] << " = { " << v[i] << " }\n";
	}
	cin.ignore();
	system("cls");
}

struct Elim_failure : std::domain_error {
	Elim_failure(std::string s) : std::domain_error(s) { }
};

struct Back_subst_failure : std::domain_error {
	Back_subst_failure(std::string s) : std::domain_error(s) { }
};

void classical_elimination(Matrixx& A, Vector& b)
{
	const Index n = A.size();

	// traverse from 1st column to the next-to-last
	// filling zeros into all elements under the diagonal:
	for (Index j = 0; j < n - 1; ++j)
	{
		const double pivot = A[j][j];
		if (pivot == 0) throw Elim_failure("Elimination failure in row " + std::to_string(j));

		// fill zeros into each element under the diagonal of the ith row:
		for (Index i = j + 1; i < n; ++i)
		{
			const double mult = A[i][j] / pivot;
			for (Index k = j; k < n; ++k)
				A[i][k] = A[j][k] * -mult + A[i][k];
			b[i] -= mult * b[j]; // make the corresponding change to b
			animated_print(A, b);
		}
	}
}

void elim_with_partial_pivot(Matrixx& A, Vector& b)
{
	const Index n = A.size();

	for (Index j = 0; j < n; ++j)
	{
		Index pivot_row = j;

		// look for a suitable pivot:
		for (Index k = j + 1; k < n; ++k)
			if (std::abs(A[k][j]) > abs(A[pivot_row][j])) pivot_row = k;

		//swap the rows if we found a better pivot:
		if (pivot_row != j)
		{
			Vector temp_row = A[pivot_row];
			A[pivot_row] = A[j];
			A[j] = temp_row;
			swap(b[j], b[pivot_row]);
			animated_print(A, b);
		}

		//elimination:
		for (Index i = j + 1; i < n; ++i)
		{
			const double pivot = A[j][j];
			if (pivot == 0) throw std::exception("can't solve: pivot==0");
			const double mult = A[i][j] / pivot;
			for (Index k = j; k < n; ++k)
				A[i][k] = A[j][k] * -mult + A[i][k];
			b[i] -= mult * b[j];
			animated_print(A, b);
		}
	}
}

Vector back_substitution(const Matrixx& A, const Vector& b)
{
	const Index n = A.size();
	Vector x(n);

	for (Index i = n - 1; i >= 0; --i)
	{
		double inner_product = 0;
		for (Index k = i + 1; k < n; ++k)
			inner_product += A[i][k] * x[k];
		double s = b[i] - inner_product;

		if (double m = A[i][i])
			x[i] = s / m;
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
	Matrixx A{
		{2, 1, -1},
		{-3, -1, 2},
		{-2, 1, 2}
	};
	Vector B{ 8, -11, -3 };

	animated_print(A, B);

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