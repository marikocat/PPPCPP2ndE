#include <iostream>
#include <fstream>

bool is_vowel(char ch)
{
	ch = tolower(ch);
	return  ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u';
}

int main()
try
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

	char ch;
	while (ifs.get(ch))
	{
		if (!is_vowel(ch))
			ofs << ch;
	}

	if (!ifs && !ifs.eof())
	{
		throw new std::runtime_error("Cannot read file in.txt");
	}
}
catch (std::exception& e)
{
	std::cerr << e.what() << std::endl;
	return 1;
}
catch (...)
{
	std::cerr << "Unknown error.\n";
	return 2;
}