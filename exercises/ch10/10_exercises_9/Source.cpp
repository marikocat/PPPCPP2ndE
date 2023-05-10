#include "..\std_lib_facilities.h"

void read_file(const string& fn, vector<string>& v)
{
	ifstream ifs{ fn };
	if (!ifs) error("cannot open ", fn);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	string s;
	while (ifs >> s)
	{
		v.push_back(s);
	}
	if (ifs.eof()) return;
	if (ifs.fail()) error("invalid file input");
}

void write_to_file(const string& fn, vector<string>& v)
{
	ofstream ofs{ fn };
	if (!ofs) error("cannot open ", fn);
	sort(v);
	for (int i = 0; i < v.size(); ++i)
	{
		ofs << v[i] << ' ';
	}
}

int main()
{
	string name = "new_file.txt";
	string name1;
	string name2;
	vector<string> buffer;

	cout << "Enter first file name: ";
	cin >> name1;
	if (!cin) error("invalid input");
	read_file(name1, buffer);

	cout << "Enter second file name: ";
	cin >> name2;
	if (!cin) error("invalid input");
	read_file(name2, buffer);

	write_to_file(name, buffer);
}