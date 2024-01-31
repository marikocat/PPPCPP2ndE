#include <iostream>

int main()
{
	std::cout << "Enter text:\n";
	for (char ch; std::cin.get(ch);)
	{
		if (std::ispunct(ch))
			ch = ' ';
		std::cout << ch;
	}
}