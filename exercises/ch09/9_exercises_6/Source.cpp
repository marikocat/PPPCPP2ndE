#include "..\std_lib_facilities.h"
#include "Chrono.h"
#include "Library.h"

using Chrono::Date;
using Chrono::Month;
using Library::Book;

int main()
try
{
    Book book{ "04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5} };
    cout << book;

    Book b1{ "16-8050-127-5",
                "Practical Vim: Edit at the Speed of Thought, 2nd Edition",
                "Drew Neil", Date{2015, Month::nov, 7} };
    Book b2{ "16-8050-127-5",
                "Practical Vim: Edit at the Speed of Thought",
                "Drew Neil", Date{2015, Month::nov, 7} };

    if (b1 == b2) cout << '\n' << b1
        << "\n-- is THE SAME book as --\n\n"
        << b2 << '\n';
    cout << "----------------------\n";
    if (book != b2) cout << '\n' << book
        << "\n-- is NOT THE SAME book as --\n\n"
        << b2 << '\n';

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