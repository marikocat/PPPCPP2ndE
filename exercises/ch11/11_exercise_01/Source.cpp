#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

void to_lower(std::string& s) // put s into lower case
{
	for (char& x : s) x = tolower(x);
}

int main()
try
{
	std::string file_name;
	std::cout << "Enter an input file name: ";
	std::cin >> file_name;

	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		throw std::runtime_error("Cannot open file " + file_name);
	}

	std::string out_file_name;
	std::cout << "Enter an output file name: ";
	std::cin >> out_file_name;

	std::ofstream ofs{ out_file_name };
	if (!ofs)
	{
		throw new std::runtime_error("Cannot open file " + file_name);
	}

	std::string line;
	while (std::getline(ifs, line))
	{
		to_lower(line);
		ofs << line << '\n';
	}

	if (!ifs && !ifs.eof())
	{
		throw new std::runtime_error("Cannot read file " + file_name);
	}
}
catch (std::runtime_error& e)
{
	std::cerr << e.what() << '\n';
}
catch (...)
{
	std::cerr << "Unknown error\n";
}