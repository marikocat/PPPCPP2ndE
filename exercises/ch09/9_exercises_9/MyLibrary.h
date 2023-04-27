#pragma once
#include "Chrono.h"

namespace MyLibrary {
	class InvalidISBN {};
	class Invalid_Book { };  // a book does not exist in the library
	class Repeated_Book { };  // a book already exists in the library
	class Invalid_Patron { }; // patron does not exist in the library
	class Repeated_Patron { }; // patron already exists in the library
	class Patron_Owes_Fees { }; // patron owes fees (sic)
	class Checked_Out_Book { }; // book is already checked out

	using Chrono::Date;

	enum class Genre {
		fiction, nonfiction, periodical, biography, children
	};

	class Book {
		string isbn;
		string title;
		string author;
		Date cdate;
		Genre gen;
		bool checkedOut;
	public:
		Book(string i, string t, string a, Date d, Genre g);
		const string& get_isbn() const { return isbn; }
		const string& get_title() const { return title; }
		const string& get_author() const { return author; }
		const Date& get_cdate() const { return cdate; }
		const Genre get_genre() const { return gen; }
		const bool checked_out() const { return checkedOut; }

		void check_out() { checkedOut = true; }
		void check_in() { checkedOut = false; }
	};

	// helper functions

	bool is_isbn(const string& isbn);
	void print(ostream& os, const Book& book);
	string get_genre_str(const Genre& genre);

	// operator overloading
	bool operator==(const Book& a, const Book& b);
	bool operator!=(const Book& a, const Book& b);
	ostream& operator<<(ostream& os, const Book& book);

	class Patron {
		string name;
		string id;
		double fee;
	public:
		Patron(string n, string num);

		void set_fee(double f);

		const string& get_name() const {
			return name;
		}
		const string& get_id() const {
			return id;
		}
		const double get_fee() const {
			return fee;
		}
	};

	// helper function
	bool owes_fee(const Patron& p);

	// operator overloading
	bool operator==(const Patron& a, const Patron& b);
	bool operator!=(const Patron& a, const Patron& b);
	ostream& operator<<(ostream& os, const Patron& p);

	class Library {
	public:
		struct Transaction {
			Book book;
			Patron patron;
			Date date;
		};

		void add_book(Book b);
		void add_patron(Patron p);
		void check_out(Book b, Patron p, Date d);

		vector<string> get_who_owes_fees() const;

		void print_books(ostream& os) const;
		void print_patrons(ostream& os) const;
		void print_transactions(ostream& os) const;
	private:
		bool is_book(const Book& b);
		bool is_patron(const Patron& p);
		Book& find_book(const Book& b);
		Patron& find_patron(const Patron& p);

		vector<Book> books;
		vector<Patron> patrons;
		vector<Transaction> transactions;
	};

	ostream& operator<<(ostream& os, const Library::Transaction& t);
}