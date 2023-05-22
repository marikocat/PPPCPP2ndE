#include <iostream>
#include <fstream>
using namespace std;

class File_handle {
	fstream fs;
public:
	File_handle(const string& s);
	~File_handle();

	fstream& get_stream() { return fs; }
};

File_handle::File_handle(const string& s)
{
	cout << "opens the file in in|out mode\n";
	fs.open(s);
}

File_handle::~File_handle()
{
	cout << "closes the file\n";
	fs.close();
}

int main()
{
	File_handle fh{ "input.txt" };
	char ch;
	string res;
	while (fh.get_stream().get(ch)) res += ch;
	cout << res << '\n';
}