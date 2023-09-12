#include "..\std_lib_facilities.h"

int main()
{
	vector<int> values;
	int v;
	cout << "Enter value: ";
	while (cin >> v) {
		if (v > 0) {
			values.push_back(v);
		}
		cout << "Enter value: ";
	}

	sort(values);

	int count = 1, max = 1;
	int mode = values[0];
	for (int i = 1; i < values.size(); i++) {
		if (values[i - 1] == values[i]) {
			count++;
			if (count > max)
			{
				max = count;
				mode = values[i];
			}
		}
		else {
			count = 1;
		}
	}

	for (int v : values)
		cout << v << " ";
	cout << "\nMode: " << mode << "\n";
}