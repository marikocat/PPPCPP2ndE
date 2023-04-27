#include "..\std_lib_facilities.h"
#include "Chrono.h"
#include "Library.h"

using Chrono::Date;
using Chrono::Month;
using Library::Book;
using Library::Genre;
using Library::Patron;

int main()
try
{
    // Test new Genre << operator through Book << operator
    Book book{ "04-6502-656-7", "Gödel, Escher, Bach: An Eternal Golden Braid",
              "Douglas Richard Hofstadter", Date{1999, Month::feb, 5},
              Genre::nonfiction };
    cout << book;

    // Test Patron type
    Patron patron{ "John Doe", "000001" };
    cout << patron;

    // Test owes_fees() helper 
    if (owes_fee(patron)) cout << "The patron has fees!\n";
    else cout << "No fees owed.\n";

    // Test Patron::set_fees()
    patron.set_fee(100);
    cout << "With fees ...\n" << patron;
    if (owes_fee(patron)) cout << "The patron has fees!\n";
    else cout << "No fees owed.\n";

    // Provoke error on Patron::set_fees()
    try {
        patron.set_fee(-100);
    }
    catch (exception& e) {
        cout << e.what() << '\n';
    }

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