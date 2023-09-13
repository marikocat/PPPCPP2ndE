#include "..\std_lib_facilities.h"

int main()
try {
	/*
	Cout << "Success!\n";
	cout << "Success!\n;
	cout << "Success" << !\n"
	cout << success << '\n';

	string res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";
	vector<int> v(10); v(5) = 7; if (v(5) != 7) cout << "Success!\n";

	if (cond) cout << "Success!\n"; else cout << "Fail!\n";
	bool c = false; if (c) cout << "Success!\n"; else cout << "Fail!\n";

	string s = "ape"; boo c = "fool" < s; if (c) cout << "Success!\n";
	string s = "ape"; if (s == "fool") cout << "Success!\n";
	string s = "ape"; if (s == "fool") cout < "Success!\n";
	string s = "ape"; if (s + "fool") cout < "Success!\n";

	vector<char> v(5); for (int i = 0; 0 < v.size(); ++i); cout << "Success!\n";
	vector<char> v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n";
	string s = "Success!\n"; for (int i = 0; i < 6; ++i) cout << s[i];
	if (true) then cout << "Success!\n"; else cout << "Fail!\n";
	int x = 2000; char c = x; if (c == 2000) cout << "Success!\n";
	string s = "Success!\n"; for (int i = 0; i < 10; ++i) cout << s[i];
	vector v(5); for (int i = 0; i <= v.size(); ++i); cout << "Success!\n";
	int i = 0; int j = 9; while (i < 10) ++j; if (j < i) cout << "Success!\n";
	int x = 2; double d = 5 / (x–2); if (d == 2 * x + 0.5) cout << "Success!\n";
	string<char> s = "Success!\n"; for (int i = 0; i <= 10; ++i) cout << s[i];
	int i = 0; while (i < 10) ++j; if (j < i) cout << "Success!\n";
	int x = 4; double d = 5 / (x–2); if (d = 2 * x + 0.5) cout << "Success!\n";
	cin << "Success!\n";*/

	cout << "Success!\n";
	cout << "Success!\n";
	cout << "Success" << "!\n";
	cout << "success" << '\n';

	int res = 7; vector<int> v(10); v[5] = res; cout << "Success!\n";
	vector<int> v2(10); v2[5] = 7; if (v2[5] == 7) cout << "Success!\n";

	if (true) cout << "Success!\n"; else cout << "Fail!\n";
	bool c = false; if (!c) cout << "Success!\n"; else cout << "Fail!\n";

	string s2 = "ape"; bool c2 = "fool" > s2; if (c2) cout << "Success!!\n";
	string s3 = "ape"; if (s3 != "fool") cout << "Success!\n";
	string s = "ape"; if (s != "fool") cout << "Success!\n";
	string s1 = "ape"; if (s1 != "fool") cout << "Success!\n";

	vector<char> v3(5); for (int i = 0; i < v3.size(); ++i); cout << "Success!\n";
	vector<char> v4(5); for (int i = 0; i < v4.size(); ++i); cout << "Success!\n";
	string s4 = "Success!\n"; for (int i = 0; i < 9; ++i) cout << s4[i];
	if (true) cout << "Success!\n"; else cout << "Fail!\n";
	int x = 2000; char c3 = x; if (c3 != 2000) cout << "Success!\n";
	string s5 = "Success!\n"; for (int i = 0; i < 9; ++i) cout << s5[i];
	vector<int> v5(5); for (int i = 0; i < v5.size(); ++i); cout << "Success!!!\n";
	int i = 0; int j = 9; while (i < 10) ++i; if (j < i) cout << "Success!\n";
	int x2 = 2; double d = 5 / (x2 - 1); if (d == 2 * (x2 + 0.5)) cout << "Success!!\n";
	string s6 = "Success!\n"; for (int i = 0; i < 10; ++i) cout << s6[i];
	int i2 = 0; while (i2 < 10) ++i2; if (j < i2) cout << "Success!\n";
	int x3 = 4; double d2 = 5 / (x3 - 2); if (d2 != 2 * (x3 + 0.5)) cout << "Success!\n";
	cout << "Success!\n";

	keep_window_open();
	return 0;
}
catch (exception& e) {
	cerr << "error: " << e.what() << '\n';
	keep_window_open();
	return 1;
}
catch (...) {
	cerr << "Oops: unknown exception!\n";
	keep_window_open();
	return 2;
}