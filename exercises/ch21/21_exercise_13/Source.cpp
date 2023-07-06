#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;

map<string, string> replacement{
	{"don't", "do not"},
	{"doesn't", "does not"},
	{"isn't", "is not"},
	{"aren't", "are not"},
	{"wasn't", "was not"},
	{"weren't", "were not"}
};

string strip_word(const string& s)
{
	string word;
	cout << "word: " << s << '\n';
	for (int i = 0; i < s.size(); ++i)
	{
		if (ispunct(s[i]) && s[i] != '\'' && s[i] != '-')
			continue;
		else
			word += tolower(s[i]);
	}
	if (replacement.find(word) != replacement.end())
		word = replacement[word];
	if (word.size() > 1)
		if (word[word.size() - 1] == 's' || word[word.size() - 1] == '\'')
		{
			word.pop_back();
			if (word[word.size() - 1] == '\'')
				word.pop_back();
		}
	return word;
}

int main()
{
	ifstream ifs{ "in.txt" };
	if (!ifs) throw exception("cannot open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	vector<string> buffer;
	for (string temp; ifs >> temp;)
	{
		buffer.push_back(strip_word(temp));
	}

	if (!ifs && !ifs.eof()) throw exception("invalid input");

	ofstream ofs{ "out.txt" };
	if (!ofs) throw exception("cannot open file");

	sort(buffer.begin(), buffer.end());
	for (string s : buffer)
		ofs << s << '\n';
}