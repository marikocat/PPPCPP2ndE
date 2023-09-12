#include "..\std_lib_facilities.h"

int main()
{
	vector<string> values;
	string input;
	cout << "Enter strings: ";
	while (cin >> input) {
		values.push_back(input);
	}

	sort(values);

	int count = 1, max = 1;
	string mode = values[0];
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

	for (string s : values)
		cout << s << " ";
	cout << "\nMin: " << values[0] << "\n";
	cout << "Max: " << values[values.size() - 1] << "\n";
	cout << "Mode: " << mode << "\n";
}