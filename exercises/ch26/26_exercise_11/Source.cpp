#include <vector>
#include <chrono>
#include <iostream>
#include "MatrixIO.h"
using namespace Numeric_lib;
using namespace std;

inline int rand_int(int max) { return rand() % max; }

inline int rand_int(int min, int max) { return rand_int(max - min) + min; }

double row_sum(Matrix<double, 2> m, int n)
{
	double s = 0;
	for (int i = 0; i < m.dim2(); ++i)
		s += m(n, i);
	return s;
}

double row_accum(Matrix<double, 2> m, int n)
{
	double s = 0;
	for (int i = 0; i < n; ++i)
		s += row_sum(m, i);
	return s;
}

void fill_matrix(Matrix<double,2>& m)
{
	for (int i = 0; i < m.dim1(); ++i)
		for (int j = 0; j < m.dim2(); ++j)
			m(i, j) = rand_int(-10, 10);
}

int main()
{
	for (int n = 50; n < 1000; n *= 10)
	{
		cout << "n == " << n << "\n";
		Matrix<double, 2> m(n, n);
		fill_matrix(m);
		vector<double> v;
		auto start = chrono::system_clock::now();
		for (int i = 0; i < m.dim1(); ++i)
			v.push_back(row_accum(m, i + 1));
		auto end = chrono::system_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "To fill the vector for Matrix(" << n << "," << n << ") took "
			<< duration.count() << " milliseconds\n";
	}
	cout << endl;
	for (int n = 50; n < 1000; n *= 10)
	{
		cout << "n == " << n << "\n";
		Matrix<double, 2> m(n, n);
		fill_matrix(m);
		vector<double> v;
		auto start = chrono::system_clock::now();
		int s = 0;
		for (int i = 0; i < m.dim1(); ++i)
		{
			s += row_sum(m, i);
			v.push_back(s);
		}
		auto end = chrono::system_clock::now();
		auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
		cout << "To fill the vector for Matrix(" << n << "," << n << ") took "
			<< duration.count() << " milliseconds\n";
	}
}