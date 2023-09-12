#include "..\std_lib_facilities.h"

int main()
{
	int sq_num = 0;
	int grains = 0;
	int total_grains = 0;
	bool flag1 = true, flag2 = true, flag3 = true;

	for (int i = 0; i < 64; i++) {
		sq_num = i + 1;
		grains = pow(2, i);
		total_grains += grains;

		if (flag1 && total_grains >= 1000)
		{
			cout << sq_num << " squares for at least 1000 grains\n";
			flag1 = false;
		}
		else if (flag2 && total_grains >= 1000000)
		{
			cout << sq_num << " squares for at least 1,000,000 grains\n";
			flag2 = false;
		}
		else if (flag3 && total_grains >= 1000000000)
		{
			cout << sq_num << " squares for at least 1,000,000,000 grains\n";
			flag3 = false;
		}
	}
}