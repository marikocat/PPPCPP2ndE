#include <iostream>

using namespace std;

int main()
{
	double d;
	double min = 0, max = 0;
	int num = 0;
	while (cin >> d)
	{
		if (num == 0)
		{
			min = d;
			max = d;
			cout << d << '\n';
		}
		else
		{
			if (d < min)
			{
				min = d;
				cout << d << " the smallest so far\n";
			}
			else if (d > max)
			{
				max = d;
				cout << d << " the largest so far\n";
			}
			else
			{
				cout << d << '\n';
			}
		}
		num++;
	}
}