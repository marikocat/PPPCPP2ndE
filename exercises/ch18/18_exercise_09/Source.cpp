#include <iostream>
using namespace std;

const int i = 10;

void memory_layout(const int* s_storage, int* stack, int* heap)
{
	if (s_storage < stack && s_storage < heap)
	{
		cout << "static storage is at lowest adresses\n";
		if (stack < heap)
		{
			cout << "stack is in the middle\n";
			cout << "heap is at highest adresses\n";
		}
		else
		{
			cout << "heap is in the middle\n";
			cout << "stack is at highest adresses\n";
		}
	}

	if (stack < s_storage && stack < heap)
	{
		cout << "stack is at lowest adresses\n";
		if (s_storage < heap)
		{
			cout << "static storage is in the middle\n";
			cout << "heap is at highest adresses\n";
		}
		else
		{
			cout << "heap is in the middle\n";
			cout << "static storage is at highest adresses\n";
		}
	}

	if (heap < s_storage && heap < stack)
	{
		cout << "heap is at lowest adresses\n";
		if (s_storage < stack)
		{
			cout << "static storage is in the middle\n";
			cout << "stack is at highest adresses\n";
		}
		else
		{
			cout << "stack is in the middle\n";
			cout << "static storage is at highest adresses\n";
		}
	}
}

int main()
{
	cout << "static storage:\n";
	cout << &i << "\n\n";

	cout << "stack:\n";
	int a[10000];
	cout << a << '\n';
	int a1[10000];
	cout << a1 << '\n';
	int a2[10000];
	cout << a2 << '\n';
	if (a2 > a) cout << "stack grows toward higher adresses\n";
	else cout << "stack grows toward lower adresses\n";
	cout << '\n';

	cout << "heap:\n";
	int* pa = new int[10000];
	cout << pa << '\n';
	int* pa1 = new int[10000];
	cout << pa1 << '\n';
	int* pa2 = new int[10000];
	cout << pa2 << '\n';
	if (pa2 > pa) cout << "heap grows toward higher adresses\n";
	else cout << "heap grows toward lower adresses\n";
	cout << '\n';

	memory_layout(&i, a, pa);
}