#include <iostream>
using namespace std;

int main()
{
	double bytes = 0;
	try
	{
		char* p;

		while (true)
		{
			p = new char[10000];
			bytes += 10000;
		}
	}
	catch (...)
	{
		cout << "bytes allocated: " << bytes << '\n';
	}
}