#include "..\std_lib_facilities.h"
#include "Chrono.h"
#include "MyLibrary.h"

using Chrono::Date;
using Chrono::Month;
using MyLibrary::Book;
using MyLibrary::Genre;
using MyLibrary::Patron;
using MyLibrary::Library;

void add_book(Library& l, Book b)
{
    try {
        l.add_book(b);
    }
    catch (MyLibrary::Repeated_Book& e) {
        cerr << "Repeated Book \"" << b.get_title() << "\" with ISBN "
            << b.get_isbn() << " !!!\n";
    }
}

void init_books(Library& l)
{
    add_book(l, Book{ "04-6502-656-7",
                    "Gödel, Escher, Bach: An Eternal Golden Braid",
                    "Douglas Richard Hofstadter",
                    Chrono::Date{1999, Chrono::Month::feb, 5},
                    Genre::nonfiction });

    add_book(l, Book{ "07-5640-474-6",
                    "The Name of the Wind",
                    "Patrick Rothfuss",
                    Chrono::Date{2008, Chrono::Month::apr, 1},
                    Genre::fiction });

    add_book(l, Book{ "17-8370-423-3",
                    "The Colour Monster",
                    "Anna Llenas",
                    Chrono::Date{2016, Chrono::Month::mar, 1},
                    Genre::children });

    add_book(l, Book{ "16-0010-483-5",
                    "Lock and Key, Vol 2: Head Games",
                    "Joe Hill and Gabriel Rodriguez",
                    Chrono::Date{2009, Chrono::Month::sep, 29},
                    Genre::periodical });

    add_book(l, Book{ "03-4552-612-0",
                    "Jim Henson: The Biography",
                    "Brian Jay Jones",
                    Chrono::Date{2016, Chrono::Month::may, 10},
                    Genre::biography });
    // Error, repeated ISBN
    add_book(l, Book{ "03-4552-612-0",
                    "Jim Henson: The Biography",
                    "Brian Jay Jones",
                    Chrono::Date{2016, Chrono::Month::may, 10},
                    Genre::biography });
}

void add_patron(Library& l, Patron p)
{
    try {
        l.add_patron(p);
    }
    catch (MyLibrary::Repeated_Patron& e) {
        cerr << "Repeated patron " << p.get_name() << " with card number "
            << p.get_id() << " !!!\n";
    }
}

void init_patrons(Library& l)
{
    add_patron(l, Patron{ "John Doe", "0000001" });
    add_patron(l, Patron{ "Peter Pan", "000032" });
    add_patron(l, Patron{ "Bobby Fisher", "000053" });
    add_patron(l, Patron{ "Max Rockatansky", "000104" });
    add_patron(l, Patron{ "Ivan Drago", "000156" });
    // Error, repeated card number
    add_patron(l, Patron{ "Bobby Fisher", "000053" });
}

void check_out(Library& l, Book b, Patron p, Chrono::Date d)
{
    try {
        l.check_out(b, p, d);
    }
    catch (MyLibrary::Invalid_Patron& e) {
        cerr << "There is no patron " << p.get_name() << " with card number "
            << p.get_id() << " !!!\n";
    }
    catch (MyLibrary::Invalid_Book& e) {
        cerr << "There is no book \"" << b.get_title() << "\" with ISBN "
            << b.get_isbn() << " !!!\n";
    }
    catch (MyLibrary::Checked_Out_Book& e) {
        cerr << "Book \"" << b.get_title() << "\" with ISBN " << b.get_isbn()
            << " is already checked out !!!\n";
    }
    catch (MyLibrary::Patron_Owes_Fees& e) {
        cerr << "Patron " << p.get_name() << " with card number "
            << p.get_id() << " owes fees !!!\n";
    }
}

void test_check_out(Library& l)
{
    Book b1{ "16-0010-483-5",
        "Lock and Key, Vol 2: Head Games",
        "Joe Hill and Gabriel Rodriguez",
        Chrono::Date{2009, Chrono::Month::sep, 29},
        Genre::periodical };

    Book b2{ "03-4552-612-0",
        "Jim Henson: The Biography",
        "Brian Jay Jones",
        Chrono::Date{2016, Chrono::Month::may, 10},
        Genre::biography };

    Book b3{ "17-8370-423-3",
        "The Colour Monster",
        "Anna Llenas",
        Chrono::Date{2016, Chrono::Month::mar, 1},
        Genre::children };

    Book b4{ "00-0000-000-0",
        "Fictional Book",
        "Fictional Author",
        Chrono::Date{2000, Chrono::Month::jan, 1},
        Genre::fiction };

    Patron p1{ "Peter Pan", "000032" };
    Patron p2{ "Bobby Fisher", "000053" };
    Patron p3{ "Max Rockatansky", "000104" };
    Patron p4{ "Invisible Man", "000000" };

    cout << '\n';
    // Test legitimate check outs
    cout << "Test legitimate check outs:\n";
    check_out(l, b1, p1, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    check_out(l, b2, p2, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    cout << "\nTRANSACTIONS ====\n\n";
    l.print_transactions(cout);

    // Invalid Book
    cout << "\nTest invalid book:\n";
    check_out(l, b4, p3, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    // Invalid Patron
    cout << "\nTest invalid patron:\n";
    check_out(l, b3, p4, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    // Book already checked out
    cout << "\nTest book checked out:\n";
    check_out(l, b2, p3, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    // Patron owes fees
    cout << "\nTest patron owes fees:\n";
    check_out(l, b3, p2, Chrono::Date{ 2017, Chrono::Month::may, 24 });

    // New legitimate check out
    cout << "\nNew legitimate check out:\n";
    check_out(l, b3, p3, Chrono::Date{ 2017, Chrono::Month::may, 24 });
    cout << "\nTRANSACTIONS ====\n\n";
    l.print_transactions(cout);

    // Debtors
    cout << "\nLIBRARY DEBTORS ====\n\n";
    for (string n : l.get_who_owes_fees())
        cout << n << '\n';
}

int main()
try
{
    Library mylib;

    init_books(mylib);
    init_patrons(mylib);

    cout << "\nLIBRARY BOOKS ===\n\n";
    mylib.print_books(cout);
    cout << "\nLIBRARY PATRONS ===\n\n";
    mylib.print_patrons(cout);

    test_check_out(mylib);

    return 0;
}
catch (Chrono::Date::Invalid& e)
{
    cerr << "Invalid date!\n";
    return 1;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception!\n";
    return 3;
}