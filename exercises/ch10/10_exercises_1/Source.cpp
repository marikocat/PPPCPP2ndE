#include "..\std_lib_facilities.h"

int main()
{
	string iname = "ints.txt";
	ifstream ifs{ iname };
	if (!ifs) error("cannot open input file ", iname);

	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	int sum = 0;
	for (int num; ifs >> num;)
		sum += num;
	if (ifs.eof()) cout << "We reached end of file.\n";
	else if (ifs.fail()) error("Wrong input");

	cout << "Sum is " << sum << "\n";
}