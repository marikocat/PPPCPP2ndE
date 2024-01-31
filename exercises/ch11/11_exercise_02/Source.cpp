#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

void to_lower(std::string& s)
{
	for (char& x : s) x = tolower(x);
}

bool contains_word(const std::string& l, const std::string& w)
{
	std::string word_to_find = w;
	to_lower(word_to_find);
	std::istringstream iss{ l };
	for (std::string word; iss >> word;)
	{
		to_lower(word);
		if (word == word_to_find)
			return true;
	}
	return false;
}

int main()
try
{
	std::cout << "Enter file name and a word to find: ";
	std::string file_name;
	std::string word;
	std::cin >> file_name >> word;
	std::ifstream ifs{ file_name };
	if (!ifs)
	{
		throw std::runtime_error("Cannot open file " + file_name);
	}

	std::string line;
	int counter = 0;
	while (std::getline(ifs, line))
	{
		counter++;
		if (contains_word(line, word))
			std::cout << counter << ": " << line << '\n';
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