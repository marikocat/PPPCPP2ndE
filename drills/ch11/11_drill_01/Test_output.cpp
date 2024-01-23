#include <iostream>
#include <iomanip>

int main()
{
	int birth_year = 1988;
	std::cout << std::showbase << birth_year << "\tdec\n" 
		<< std::hex << birth_year << "\thex\n"
		<< std::oct << birth_year << "\toct\n" << std::dec;
	std::cout << 35 << "\n";

	int a, b, c, d;
	std::cin >> a >> std::oct >> b >> std::hex >> c >> d;
	std::cout << a << '\t' << b << '\t' << c << '\t' << d << '\n';

	double f = 1234567.89;
	std::cout << f << "\tdefaultfloat\n"
		<< std::fixed << f << "\tfixed\n"
		<< std::scientific << f << "\tscientific\n";
	std::cout << "Default precision: 6.\n";

	std::cout << std::setw(15) << std::left << "last_name" << '|' 
		<< std::setw(15) << "first_name" << '|' 
		<< std::setw(20) << "telephone_number" << '|' 
		<< std::setw(15) << "email_address" << '|' << "\n";
}