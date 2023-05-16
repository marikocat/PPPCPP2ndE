#include <iostream>
using namespace std;

bool is_palindrome(const char s[], int n)
{
	int first = 0;
	int last = n - 1;
	while (first < last)
	{
		if (s[first] != s[last]) return false;
		++first;
		--last;
	}
	return true;
}

istream& read_word(istream& is, char* buffer, int max)
{
	is.width(max); // read at most max-1 characters in the next>>
	is >> buffer; // read whitespace-terminated word,
					// add zero after the last character read into buffer
	if (is.peek() != '\n')
	{
		cout << "an input string was too long: max size = " << max - 1 << '\n';
		char ch;
		while (is.get(ch))
		{
			if (isspace(ch)) break;
		}
	}
	return is;
}

istream& read_long_string(istream& is, char*& buffer)
{
	int limit = 5;
	buffer = new char[limit];

	char ch;
	int i = 0;
	for (; is.get(ch); ++i)
	{
		if (ch == '\n') break;
		if (i == limit - 1)
		{
			char* temp = buffer;
			limit *= 2;
			buffer = new char[limit];
			copy(temp, &temp[limit / 2 - 1], buffer);
			delete[] temp;
		}
		buffer[i] = ch;
	}
	buffer[i] = '\0';
	return is;
}

int main()
{
	constexpr int max = 10;
	char s[max];
	if (read_word(cin, s, max))
	{
		cout << s << " is";
		if (!is_palindrome(s, strlen(s))) cout << " not";
		cout << " a palindrome\n";
	}

	char* p = nullptr;
	while (read_long_string(cin, p) && p)
	{
		cout << p << " is";
		if (!is_palindrome(p, strlen(p))) cout << " not";
		cout << " a palindrome\n";
	}
}