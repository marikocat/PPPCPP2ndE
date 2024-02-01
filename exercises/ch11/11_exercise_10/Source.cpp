#include <iostream>
#include <sstream>
#include <vector>

std::vector<std::string> split(const std::string& s)
{
	std::vector<std::string> res;
	std::istringstream iss(s);
	for (std::string word; iss >> word;)
		res.push_back(word);
	return res;
}

int main()
{
	std::string s{ "don't use the as-if rule" };
	std::vector<std::string> v = split(s);
	for (auto& el : v)
		std::cout << el << std::endl;
}