#include "..\std_lib_facilities.h"
#include "Library.h"

namespace Library {
	
	Book::Book(string i, string t, string a, Date d)
		: isbn{i}, title{t}, author{a}, cdate{d}
	{
		if (!is_isbn(isbn)) throw InvalidISBN{};
	}
		

	// helper functions

	bool is_isbn(const string& isbn)
	{
		int hyphenNum{ 0 };
		bool num{ false };

		int limit = isbn.size();
		for (int i = 0; i < limit; i++)
		{
			char ch{ isbn[i] };
			if (hyphenNum < 3)
			{
				if (!isdigit(ch))
				{
					if (ch == '-' && num)
					{
						++hyphenNum;
						num = false;
					}
					else
					{
						return false;
					}
				}
				else
				{
					num = true;
				}
			}
			else
			{
				if (i != limit - 1) return false;
				return (isdigit(ch) || isalpha(ch));
			}
		}
	}

	void print(ostream& os, const Book& book)
	{
		os << "Title: " << book.get_title() << "\n"
			<< "Author: " << book.get_author() << "\n"
			<< "ISBN: " << book.get_isbn() << "\n"
			<< "Copyright date: " << book.get_cdate() << "\n"
			<< "Checked: ";
		if (book.checked_out()) os << "OUT\n\n";
		else os << "IN\n\n";
	}
}