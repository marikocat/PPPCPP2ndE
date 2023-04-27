#include "..\std_lib_facilities.h"
#include "MyLibrary.h"

namespace MyLibrary {
	
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

	// operator overloading
	bool operator==(const Patron& a, const Patron& b)
	{
		return (a.get_id() == b.get_id());
	}
	bool operator!=(const Patron& a, const Patron& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Patron& p)
	{
		os << "User's name: " << p.get_name() << '\n'
			<< "Card number: " << p.get_id() << '\n'
			<< "Fees owed:   " << p.get_fee() << '\n';

		return os;
	}

	void Library::add_book(Book b)
	{
		if (is_book(b)) throw Repeated_Book{};
		books.push_back(b);
	}

	void Library::add_patron(Patron p)
	{
		if (is_patron(p)) throw Repeated_Patron{};
		patrons.push_back(p);
	}

	void Library::check_out(Book b, Patron p, Date d)
	{
		if (!is_book(b)) throw Invalid_Book{};
		Book& lb = find_book(b);
		if (lb.checked_out()) throw Checked_Out_Book{};

		if (!is_patron(p)) throw Invalid_Patron{};
		Patron& lp = find_patron(p);
		if (owes_fee(lp)) throw Patron_Owes_Fees{};

		transactions.push_back(Transaction{ b, p, d });
		lb.check_out();
		lp.set_fee(10.0);
	}

	vector<string> Library::get_who_owes_fees() const
	{
		vector<string> namesWithFees;

		for (Patron p : patrons)
			if (owes_fee(p)) namesWithFees.push_back(p.get_name());

		return namesWithFees;
	}

	void Library::print_books(ostream& os) const
	{
		for (Book b : books)
			os << b;
	}

	void Library::print_patrons(ostream& os) const
	{
		for (Patron p : patrons)
			os << p;
	}

	void Library::print_transactions(ostream& os) const
	{
		for (Transaction t : transactions)
			os << t;
	}

	bool Library::is_book(const Book& b)
	{
		for (Book book : books)
			if (book == b) return true;
		return false;
	}

	bool Library::is_patron(const Patron& p)
	{
		for (Patron patron : patrons)
			if (patron == p) return true;
		return false;
 	}

	Book& Library::find_book(const Book& b)
	{
		for (Book& book : books)
			if (book == b) return book;
		throw Invalid_Book{};
	}

	Patron& Library::find_patron(const Patron& p)
	{
		for (Patron& patron : patrons)
			if (patron == p) return patron;
		throw Invalid_Patron{};
	}

	ostream& operator<<(ostream& os, const Library::Transaction& t)
	{
		os << t.patron.get_name() << " got " << t.book.get_title() << " (ISBN: "
			<< t.book.get_isbn() << ") on " << t.date << "\n";

		return os;
	}
}