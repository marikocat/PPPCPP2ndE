#pragma once
#include "Chrono.h"

namespace Library {
	class InvalidISBN {};
	using Chrono::Date;

	class Book {
		string isbn;
		string title;
		string author;
		Date cdate;
		bool checkedOut;
	public:
		Book(string i, string t, string a, Date d);
		const string& get_isbn() const { return isbn; }
		const string& get_title() const { return title; }
		const string& get_author() const { return author; }
		const Date& get_cdate() const { return cdate; }
		const bool checked_out() const { return checkedOut; }

		void check_out() { checkedOut = true; }
		void check_in() { checkedOut = false; }
	};

	// helper functions

	bool is_isbn(const string& isbn);
	void print(ostream& os, const Book& book);
}