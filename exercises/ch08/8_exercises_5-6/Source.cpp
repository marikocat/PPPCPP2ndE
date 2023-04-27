#include "..\std_lib_facilities.h"

vector<int> reverse(const vector<int>& v)
{
	vector<int> temp;
	for (int i = v.size() - 1; i >= 0; i--)
	{
		temp.push_back(v[i]);
	}
	return temp;
}

void reverse2(vector<int>& v)
{
	int middle = v.size() / 2;
	int last_index = v.size() - 1;
	for (int i = 0; i < middle; i++) {
		swap(v[i], v[last_index - i]);
	}
}

vector<string> reverse_string(const vector<string>& v)
{
	vector<string> temp;
	for (int i = v.size() - 1; i >= 0; i--)
	{
		temp.push_back(v[i]);
	}
	return temp;
}

void reverse_string2(vector<string>& v)
{
	int middle = v.size() / 2;
	int last_index = v.size() - 1;
	for (int i = 0; i < middle; i++) {
		swap(v[i], v[last_index - i]);
	}
}

int main()
{
	vector<int> v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	for (int i : v)
		cout << i << " ";
	cout << "\n";
	v = reverse(v);
	for (int i : v)
		cout << i << " ";
	cout << "\n";
	reverse2(v);
	for (int i : v)
		cout << i << " ";
	cout << "\n";
	vector<string> v2 = { "hello", "hi", "nice", "let" };
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
	v2 = reverse_string(v2);
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
	reverse_string2(v2);
	for (string s : v2)
		cout << s << " ";
	cout << "\n";
}