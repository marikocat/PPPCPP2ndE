#include <iostream>
#include <string>
using namespace std;

bool is_palindrome(const string& s)
{
	string temp;
	for (int i = s.size() - 1; i >= 0; --i)
	{
		temp.push_back(s[i]);
	}
	if (s == temp)
		return true;
	return false;
}

bool is_palindrome(const char s[], int n)
{
	char* p = new char[n];
	for (int i = n - 1, j = 0; i >= 0; --i, ++j)
	{
		p[j] = s[i];
	}
	for (int i = 0; i < n; ++i)
	{
		if (s[i] != p[i])
		{
			delete[] p;
			return false;
		}
	}
	delete[] p;
	return true;
}

bool is_palindrome(const char* first, const char* last)
{
	int size = last - first + 1;
	char* p = new char[size];
	for (int i = 0; i < size; ++i)
	{
		p[i] = *last;
		--last;
	}
	for (int i = 0; i < size; ++i)
	{
		if (p[i] != *first)
		{
			delete[] p;
			return false;
		}
		++first;
	}
	delete[] p;
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
	is.width(max); // read at most max-1 characters in the next>>
	is >> buffer; // read whitespace-terminated word,
					// add zero after the last character read into buffer
	return is;
}

int main()
{
	string s;
	if (getline(cin, s)) // reads with whitespace
	{
		cout << "functions with string: " << s << " is";
		if (!is_palindrome(s)) cout << " not";
		cout << " a palindrome\n";
	}

	constexpr int max = 128;
	char s2[max];
	if (read_word(cin, s2, max))
	{
		cout << "function with char array: " << s2 << " is";
		if (!is_palindrome(s2, strlen(s2))) cout << " not";
		cout << " a palindrome\n";
	}

	char s3[max];
	if (read_word(cin, s3, max))
	{
		cout << s3 << " is";
		if (!is_palindrome(&s3[0], &s3[strlen(s3) - 1])) cout << " not";
		cout << " a palindrome\n";
	}
}