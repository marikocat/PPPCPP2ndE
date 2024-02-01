#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>

int main()
try
{
    std::ifstream ifs("in.txt");
    if (!ifs)
    {
        throw std::runtime_error("Cannot open file in.txt");
    }

    std::vector<double> nums;
    for (double d; ifs >> d;)
        nums.push_back(d);

    std::cout << std::scientific << std::setprecision(8);
    for (int i = 0; i < nums.size(); ++i)
    {
        if (i % 4 == 0 && i != 0)
            std::cout << std::endl;
        std::cout << std::setw(20) << nums[i];
    }
    std::cout << std::endl;
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