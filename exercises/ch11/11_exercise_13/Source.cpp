#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

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

	std::vector<std::string> v;
	for (std::string line; std::getline(ifs, line);)
	{
		std::vector<std::string> words;
		std::istringstream iss(line);
		for (std::string word; iss >> word;)
			words.push_back(word);
		line = "";
		for (int i = words.size() - 1; i >= 0; --i)
		{
			line += words[i];
			if (i == 0)
				line += '\n';
			else
				line += ' ';
		}
		v.push_back(line);
		line = "";
	}

	for (int i = v.size() - 1; i >= 0; --i)
	{
		ofs << v[i];
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