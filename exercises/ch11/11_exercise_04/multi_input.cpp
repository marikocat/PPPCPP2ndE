#include <iostream>

int main()
try
{
	std::cout << "Enter several integers in any combination of octal, decimal, or hexadecimal, using the 0 and 0x base suffixes:\n"
		<< std::showbase;
	for (char ch; std::cin >> ch;)
	{
		int i;
		if (ch == '0')
		{
			std::cin.get(ch);
			if (ch == 'x')
			{
				std::cin >> std::hex >> i;
				std::cout << std::hex << i << "\thex\t";
			}
			else if (isdigit(ch))
			{
				std::cin.unget();
				std::cin >> std::oct >> i;
				std::cout << std::oct << i << "\toct\t";
			}
			else if (isspace(ch))
			{
				i = 0;
				std::cout << i << "\tdec\t";
			}
		}
		else if (isdigit(ch))
		{
			std::cin.unget();
			std::cin >> std::dec >> i;
			std::cout << i << "\tdec\t";
		}
		else
		{
			throw std::runtime_error("Not a number");
		}
		std::cout << "converts to\t" << std::dec << i << "\tdec\n";
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