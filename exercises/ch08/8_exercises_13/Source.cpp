#include "..\std_lib_facilities.h"

void print(const string& label, const vector<int>& data)
// Only read arguments, so it safe to pass them by const-reference
{
	cout << label << ": { ";
	for (int i : data)
		cout << i << ' ';
	cout << "}\n";
}

void print(const string& label, const vector<string>& data)
// Only read arguments, so it safe to pass them by const-reference
{
	cout << label << ": { ";
	for (string i : data)
		cout << "\"" << i << "\" ";
	cout << "}\n";
}

vector<int> num_of_chars(const vector<string>& v)
{
	int limit = v.size();
	vector<int> temp(limit);
	for (int i = 0; i < limit; i++) {
		temp[i] = v[i].size();
	}
	return temp;
}

vector<string> find_longest_str(const vector<string>& v)
{
	int max{ int(v[0].size()) };
	for (string s : v) {
		if (max < s.size()) max = s.size();
	}
	vector<string> temp;
	for (string s : v) {
		if (s.size() == max) temp.push_back(s);
	}

	return temp;
}

vector<string> find_shortest_str(const vector<string>& v)
{
	int min{ int(v[0].size()) };
	for (string s : v) {
		if (min > s.size()) min = s.size();
	}
	vector<string> temp;
	for (string s : v) {
		if (s.size() == min) temp.push_back(s);
	}

	return temp;
}

string lex_first_string(const vector<string>& v) {
	vector<string> temp{ v };
	sort(temp.begin(), temp.end());
	return temp[0];
}

string lex_last_string(const vector<string>& v) {
	vector<string> temp{ v };
	sort(temp.begin(), temp.end());
	return temp[temp.size() - 1];
}

int main()
{
	vector<string> data{ "one", "two", "three", "four", "five", "six", "seven" };
	print("vector of ints: ", num_of_chars(data));
	print("vector of longest strings: ", find_longest_str(data));
	print("vector of shortest string: ", find_shortest_str(data));
	cout << "lexicographically first string: " << lex_first_string(data) << "\n";
	cout << "lexicographically last string: " << lex_last_string(data) << "\n";
}