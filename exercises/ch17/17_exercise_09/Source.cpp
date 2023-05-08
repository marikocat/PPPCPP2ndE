#include <iostream>
using namespace std;

int main()
{
	int x[100];
	int y[100];
	cout << x << ' ' << y << '\n';
	cout << &x << ' ' << &y << '\n';
	if (x < y) cout << "stack grows toward higher addresses\n";
	else cout << "stack grows toward lower addresses\n";

	int* p1 = new int[100];
	int* p2 = new int[100];
	cout << p1 << ' ' << p2 << '\n';
	if (p1 < p2) cout << "heap grows toward higher addresses\n";
	else cout << "heap grows toward lower addresses\n";
}