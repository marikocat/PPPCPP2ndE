#include "..\std_lib_facilities.h"

int main()
{
	string s1, s2, s3;
	cout << "Enter three strings: ";
	cin >> s1 >> s2 >> s3;

	string tmp;
	if (s1 > s2) {
		tmp = s2;
		s2 = s1;
		s1 = tmp;
	}
	if (s2 > s3) {
		tmp = s3;
		s3 = s2;
		s2 = tmp;
	}
	if (s1 > s2) {
		tmp = s2;
		s2 = s1;
		s1 = tmp;
	}

	cout << s1 << ", " << s2 << ", " << s3 << "\n";

	return 0;
}