#include <iostream>
#include <fstream>

int main()
{
	std::ifstream ifs("in.txt");
	if (!ifs)
	{
		throw std::runtime_error("Cannot open file in.txt");
	}

	std::ofstream ofs("out.txt");
	if (!ofs)
	{
		throw std::runtime_error("Cannot open file out.txt");
	}

	std::string s;
	for (char ch; ifs.get(ch);)
	{
		s += ch;
	}

	for (int i = s.size() - 1; i >=0; --i)
	{
		ofs << s[i];
	}
}