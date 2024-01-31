#include <iostream>
#include <string>
#include <vector>

void to_lower(std::string& s)
{
	for (auto& c : s)
	{
		c = tolower(c);
	}
}

bool replace_substring(std::string& s)
{
	static const std::vector<std::string> v1
	{
		"isn't", "aren't", "can't", "couldn't", "don't", "doesn't", "haven't", "hasn't", "won't"
	};
	static const std::vector<std::string> v2
	{
		"is not", "aren not", "cannot", "could not", "do not", "does not", "haven't", "has not", "will not"
	};

	for (int i = 0; i < v1.size(); ++i)
	{
		size_t index = s.find(v1[i]);
		if (index != std::string::npos)
		{
			s.replace(index, v1[i].length(), v2[i]);
			return true;
		}
	}
	return false;
}

void strip_punct(std::string& s)
{
	for (int i = 0; i < s.length(); ++i)
	{
		if (ispunct(s[i]))
		{
			if (s[i] == '-')
			{
				if (i > 0 && i < s.length() - 1 && isalpha(s[i - 1]) && isalpha(s[i + 1]))
					continue;
			}
			s[i] = ' ';
		}
	}
}

int main()
{
	std::cout << "Enter text:\n";
	for (std::string line; std::getline(std::cin, line);)
	{
		to_lower(line);
		replace_substring(line);
		strip_punct(line);
		std::cout << line << std::endl;
	}
}