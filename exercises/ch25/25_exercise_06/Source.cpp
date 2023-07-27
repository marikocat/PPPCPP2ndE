#include <iostream>
using namespace std;

int main()
{
	for (char ch = 0; ch < 128; ++ch)
		cout << int(ch) << '\n';
}