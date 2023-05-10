#include "..\std_lib_facilities.h"

int read_file(const string& fn)
{
	ifstream ifs(fn);
	if (!ifs) error("cannot open ", fn);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	char ch;
	int sum = 0;
	while (ifs >> ch)
	{
		if (isdigit(ch))
		{
			ifs.putback(ch);
			int i;
			ifs >> i;
			sum += i;
		}
	}
	if (ifs.eof()) return sum;
	if (ifs.fail()) error("invalid file input");
}

int main()
{
	string ifile = "input_file.txt";
	cout << "Sum of all integers in file is: " << read_file(ifile) << '\n';
}