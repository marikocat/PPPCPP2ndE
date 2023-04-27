#include "..\std_lib_facilities.h"

void swap_v(int a, int b);
void swap_r(int& a, int& b);
void swap_cr(const int&, const int&);

int main()
{
	int x = 7;
	int y = 9;
	swap_r(x, y); // replace ? by v, r, or cr
	cout << x << " " << y << "\n";
	// swap_r(7, 9);
	cout << x << " " << y << "\n";
	const int cx = 7;
	const int cy = 9;
	// swap_r(cx, cy);
	cout << x << " " << y << "\n";
	// swap_r(7.7, 9.9);
	cout << x << " " << y << "\n";
	double dx = 7.7;
	double dy = 9.9;
	// swap_r(dx, dy);
	cout << x << " " << y << "\n";
	//swap_r(7.7, 9.9);
	cout << x << " " << y << "\n";
}

void swap_v(int a, int b)
{
	int temp; temp = a; a = b; b = temp;
}

void swap_r(int& a, int& b)
{
	int temp; temp = a; a = b; b = temp;
}

void swap_cr(const int& a, const int& b)
{
	// int temp; temp = a; a = b; b = temp;
}