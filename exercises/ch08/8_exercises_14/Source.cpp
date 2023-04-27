#include "..\std_lib_facilities.h"

void f(const int i)
{
	cout << i << "\n";
}

int main()
{
	const int x = 10;
	f(x);
	int y = 100;
	f(y);
	constexpr int z = 150;
	f(z);
	f(1500);
}