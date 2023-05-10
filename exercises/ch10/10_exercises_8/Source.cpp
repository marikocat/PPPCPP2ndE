#include "..\std_lib_facilities.h"

void read_file(const string& fn, vector<char>& v)
{
	ifstream ifs{ fn };
	if (!ifs) error("cannot open ", fn);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);
	char ch = 0;
	while (ifs.get(ch))
	{
		v.push_back(ch);
	}
	if (ifs.eof()) return;
	if (ifs.fail()) error("invalid file input");
}

void write_to_file(const string& fn, const vector<char>& v)
{
	ofstream ofs{ fn };
	if (!ofs) error("cannot open ", fn);
	for (int i = 0; i < v.size(); ++i)
	{
		ofs << v[i];
	}
}

int main()
{
	string name = "new_file.txt";
	string name1;
	string name2;
	vector<char> buffer;

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