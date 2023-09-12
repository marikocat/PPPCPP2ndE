#include "..\std_lib_facilities.h"
#include <climits>

int main()
{
	int sq_num = 0;

	int grains = 0;
	int total_grains = 0;

	double d_grains = 0;
	double d_total_grains = 0;

	bool flag1 = true, flag2 = true;

	for (int i = 0; i < 1024; i++) {
		sq_num = i + 1;
		grains = pow(2, i);
		total_grains += grains;
		d_grains = pow(2, i);
		d_total_grains += d_grains;

		if (flag1 && d_total_grains > INT_MAX)
		{
			cout << "INT_MAX = " << INT_MAX << '\n';
			cout << "The number of squares for which you can calculate the exact number of grains (using an int) is " << i << "\n";
			flag1 = false;
		}

		if (flag1)
		{
			cout << "Square " << sq_num << " with " << grains << " grains\n";
			cout << "Total number of grains: " << total_grains << "\n";
		}

		if (flag2 && d_total_grains > DBL_MAX)
		{
			cout << "DBL_MAX = " << DBL_MAX << '\n';
			cout << "The number of squares for which you can calculate the exact number of grains (using a double) is " << i << "\n";
			flag2 = false;
		}

		if (flag2)
		{
			cout << "Square " << sq_num << " with " << d_grains << " grains (double)\n";
			cout << "Total number of grains (double): " << d_total_grains << "\n";
		}
	}
}