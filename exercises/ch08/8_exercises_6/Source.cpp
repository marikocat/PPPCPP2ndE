#include "..\std_lib_facilities.h"

vector<string> reverse_vs(const vector<string>& v)
{
	vector<string> temp;
	for (int i = v.size() - 1; i >= 0; i--)
	{
		temp.push_back(v[i]);
	}
	return temp;
}

void reverse_vs2(vector<string>& v)
{
	int middle = v.size() / 2;
	int last_index = v.size() - 1;
	for (int i = 0; i < middle; i++) {
		swap(v[i], v[last_index - i]);
	}
}

int main()
{
	vector<string> v2 = { "hello", "hi", "nice", "let" };
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
	v2 = reverse_vs(v2);
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
	reverse_vs2(v2);
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
}