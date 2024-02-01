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

bool is_whitespace(char c, const std::string& w)
{
	for (char ch : w)
		if (c == ch) return true;
	return false;
}

std::vector<std::string> split(const std::string& s, const std::string& w)
{
	std::string ws = s;
	for (char& ch : ws)
	{
		if (is_whitespace(ch, w))
			ch = ' ';
	}
	return split(ws);
}

int main()
{
	std::string s{ "don't, use the as-if!rule." };
	std::vector<std::string> v = split(s, ",!.");
	for (auto& el : v)
		std::cout << el << std::endl;
}