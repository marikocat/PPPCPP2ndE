#include <iostream>
#include <fstream>

int main()
try
{
	std::ifstream ifs("in.txt");
	if (!ifs)
	{
		throw std::runtime_error("Cannot open file in.txt");
	}
	std::ofstream ofsb("outb", std::ios_base::binary);
	if (!ofsb)
	{
		throw std::runtime_error("Cannot open file outb");
	}
	int n;
	while (ifs>>n)
	{
		ofsb.write(reinterpret_cast<char*>(&n), sizeof(n));
	}
	ofsb.close();

	std::ifstream ifsb("outb", std::ios_base::binary);
	if (!ifsb)
	{
		throw std::runtime_error("Cannot open file outb");
	}
	std::ofstream ofs("out.txt");
	if (!ofs)
	{
		throw std::runtime_error("Cannot open file out.txt");
	}
	while (ifsb.read(reinterpret_cast<char*>(&n), sizeof(n)))
	{
		std::cout << n << " ";
		ofs << n << " ";
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