#include <iostream>
#include <string>
#include <vector>
#include <fstream>

int main()
try
{
    std::ifstream ifs("in.txt");
    if (!ifs)
    {
        throw std::runtime_error("Cannot open file in.txt");
    }
    std::vector<int> numbers(11, 0);
    std::vector<std::string> categories{ 
        "\tisspace", "\tisalpha", "\tisdigit", "\tisxdigit", "\tisupper", "\tislower", "\tisalnum", "\tiscntrl", "\tispunct", "\tisprint", "\tisgraph" };
    for (char ch; ifs.get(ch);)
    {
        std::cout << ch;
        if (std::isspace(ch)) numbers[0]++;
        if (std::isalpha(ch)) numbers[1]++;
        if (std::isdigit(ch)) numbers[2]++;
        if (std::isxdigit(ch)) numbers[3]++;
        if (std::isupper(ch)) numbers[4]++;
        if (std::islower(ch)) numbers[5]++;
        if (std::isalnum(ch)) numbers[6]++;
        if (std::iscntrl(ch)) numbers[7]++;
        if (std::ispunct(ch)) numbers[8]++;
        if (std::isprint(ch)) numbers[9]++;
        if (std::isgraph(ch)) numbers[10]++;
    }
    std::cout << std::endl;
    for (int i = 0; i < numbers.size(); ++i)
    {
        std::cout << numbers[i] << "\t-" << categories[i] << std::endl;
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