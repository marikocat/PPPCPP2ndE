#include <iostream>
#include <regex>
using namespace std;

int main()
{
	regex pat{ "." };
	string s{ "\n" };
	smatch matches;
	if (regex_match(s, matches, pat)) cout << "dot special character matches a newline\n";
	else cout << "dot special character doesn't match a newline\n";
}