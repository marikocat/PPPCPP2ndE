#include <iostream>
#include <string>

int main()
{
	for (std::string s; std::getline(std::cin, s);)
	{
        for (int i = 0; i < s.size(); ++i)
        {
            std::cout << s[i];
            if (isspace(s[i])) std::cout << "\tisspace";
            if (isalpha(s[i])) std::cout << "\tisalpha";
            if (isdigit(s[i])) std::cout << "\tisdigit";
            if (isxdigit(s[i])) std::cout << "\tisxdigit";
            if (isupper(s[i])) std::cout << "\tisupper";
            if (islower(s[i])) std::cout << "\tislower";
            if (isalnum(s[i])) std::cout << "\tisalnum";
            if (iscntrl(s[i])) std::cout << "\tiscntrl";
            if (ispunct(s[i])) std::cout << "\tispunct";
            if (isprint(s[i])) std::cout << "\tisprint";
            if (isgraph(s[i])) std::cout << "\tisgraph";
            std::cout << std::endl;
        }
	}
}