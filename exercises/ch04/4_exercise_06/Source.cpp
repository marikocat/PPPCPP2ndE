#include <iostream>
#include <vector>

using namespace std;

int main()
{
	vector<string> nums{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
	int n;
	string s;
	while (cin >> n >> s)
	{
		cout << n << " --> " << nums[n] << '\n';

		for (int i = 0; i < nums.size(); ++i)
		{
			if (s == nums[i])
				cout << s << " --> " << i << '\n';
		}
	}
}