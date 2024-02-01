#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main()
try
{
    std::ifstream ifs("in.txt");
    if (!ifs)
    {
        throw std::runtime_error("Cannot open file in.txt");
    }

    std::vector<int> nums;
    for (int n; ifs >> n;)
        nums.push_back(n);
    std::sort(nums.begin(), nums.end());
    int repeats = 1;
    for (int i = 1; i < nums.size(); ++i)
    {
        if (nums[i] == nums[i - 1])
        {
            repeats++;
            if (i != nums.size() - 1)
                continue;
            std::cout << nums[i];
        }
        else
        {
            std::cout << nums[i - 1];
        }
        if (repeats > 1) std::cout << " " << repeats;
        std::cout << std::endl;
        repeats = 1;
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