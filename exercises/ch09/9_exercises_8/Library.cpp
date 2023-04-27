#include "..\std_lib_facilities.h"
#include "Library.h"

namespace Library {
	
	Book::Book(string i, string t, string a, Date d, Genre g)
		: isbn{ i }, title{ t }, author{ a }, cdate{ d }, gen{ g }, checkedOut{ false }
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
			<< "Genre: " << get_genre_str(book.get_genre()) << "\n"
			<< "Checked: ";
		if (book.checked_out()) os << "OUT\n\n";
		else os << "IN\n\n";
	}

	string get_genre_str(const Genre& genre)
	{
		vector<string> genres{ "fiction", "nonfiction", "periodical", "biography", "children" };
		return genres[int(genre)];
	}

	// operator overloading
	bool operator==(const Book& a, const Book& b)
	{
		return (a.get_isbn() == b.get_isbn());
	}
	bool operator!=(const Book& a, const Book& b)
	{
		return !(a == b);
	}
	ostream& operator<<(ostream& os, const Book& book)
	{
		os << "Title: " << book.get_title() << "\n"
			<< "Author: " << book.get_author() << "\n"
			<< "Genre: " << get_genre_str(book.get_genre()) << "\n"
			<< "ISBN: " << book.get_isbn() << "\n\n";
		return os;
	}

	Patron::Patron(string n, string num)
		: name{ n }, id{ num }, fee{0}
	{

	}

	void Patron::set_fee(double f)
	{
		if (f < 0) error("\nnegative fee\n");
		fee = f;
	}

	// helper function 

	bool owes_fee(const Patron& p)
	{
		return (p.get_fee() != 0);
	}

	ostream& operator<<(ostream& os, const Patron& p)
	{
		os << "User's name: " << p.get_name() << '\n'
			<< "Card number: " << p.get_id() << '\n'
			<< "Fees owed:   " << p.get_fee() << '\n';

		return os;
	}
}