#include "..\std_lib_facilities.h"

long int iround(double d)
{
    return (d < 0.0) ? (d - 0.5) : (d + 0.5);
}

enum class Currency {
    USD, EUR, GBP
};

const vector<string> currencies = { "USD ", "EUR ", "GBP " };

ostream& operator<<(ostream& os, const Currency currency)
{
    os << currencies[int(currency)];
    return os;
}

class Money {
    long int amount_in_cents;
    Currency currency;
public:
    class DivisionByZero {};
    class IllegalMoneyOperation {};

    Money(long int d, long int c, Currency cur);
    Money(long int a, Currency cur);
    Money(double a, Currency cur);
    Money();

    long int get_amount_in_cents() const { return amount_in_cents; }
    Currency get_currency() const { return currency; }

    long int get_dollars() const { return amount_in_cents / 100; }
    long int get_cents() const { return amount_in_cents % 100; }
};

Money::Money(long int d, long int c, Currency cur)
    : amount_in_cents{ d * 100 + c }, currency{cur}
{
}

Money::Money(long int a, Currency cur) 
    : amount_in_cents{ a }, currency{ cur }
{
}

Money::Money(double a, Currency cur)
    : amount_in_cents{(long int)(a * 100)}, currency{cur}
{

}

Money::Money() : amount_in_cents{ 0 }, currency{Currency::USD}
{
}

Money operator-(const Money& m)
{
    return Money{ -m.get_amount_in_cents(), m.get_currency() };
}

Money operator+(const Money& m1, const Money& m2)
{
    if (m1.get_currency() != m2.get_currency()) throw Money::IllegalMoneyOperation{};
    return Money{ m1.get_amount_in_cents() + m2.get_amount_in_cents(), m1.get_currency() };
}

Money operator-(const Money& m1, const Money& m2)
{
    if (m1.get_currency() != m2.get_currency()) throw Money::IllegalMoneyOperation{};
    return Money{ m1.get_amount_in_cents() - m2.get_amount_in_cents(), m1.get_currency() };
}

Money operator*(const Money& m, double d)
{
    return Money{ iround(m.get_amount_in_cents() * d), m.get_currency() };
}

Money operator*(double d, const Money& m)
{
    return Money{ iround(d * m.get_amount_in_cents()), m.get_currency() };
}

Money operator/(const Money& m, double d)
{
    if (d == 0) throw Money::DivisionByZero{};

    return Money{ iround(m.get_amount_in_cents() / d), m.get_currency() };
}

double operator/(const Money& m1, const Money& m2)
{
    if (m1.get_currency() != m2.get_currency()) throw Money::IllegalMoneyOperation{};
    if (m2.get_amount_in_cents() == 0) throw Money::DivisionByZero{};

    return double(m1.get_amount_in_cents()) / m2.get_amount_in_cents();
}

bool operator==(const Money& m1, const Money& m2)
{
    if (m1.get_currency() != m2.get_currency()) throw Money::IllegalMoneyOperation{};
    return (m1.get_amount_in_cents() == m2.get_amount_in_cents());
}

bool operator!=(const Money& m1, const Money& m2)
{
    if (m1.get_currency() != m2.get_currency()) throw Money::IllegalMoneyOperation{};
    return !(m1 == m2);
}

ostream& operator<<(ostream& os, const Money& m)
{
    os << m.get_currency() << m.get_dollars() << '.';
    if (abs(m.get_cents()) < 10) os << '0';
    os << abs(m.get_cents());

    return os;
}

int main()
try {

    // Test Money*double, double*Money, Money/Money, Money/double, Money-Money
    // and <<
    Money budget{ 1000000, 0, Currency::USD };
    Money wage{ 1500, 0, Currency::USD };
    long int months{ 18 };
    long int workers{ iround(budget / (wage * months)) };
    Money surplus{ budget - (workers * wage * months) };
    cout << "The project's budget ascends to " << budget
        << " and it will be developed during " << months << " months.\n"
        << "Each developer get " << wage << " per month. "
        << "So we can hire " << workers << " developers.\n"
        << "The spare budget will be " << surplus << ".\n";

    cout << '\n';

    // Test Money*double, Money+Money and <<
    Money product{ 134, 0, Currency::USD };
    double vat = 0.21;
    Money total{ product + (product * vat) };
    cout << "You have bought and paid by transference " << product
        << " for a product. But you forgot the VAT (" << vat * 100
        << "%).\n" << "With VAT applied the product costs " << total
        << " so you debt " << product - total << '\n';

    cout << '\n';

    // Test and justify Money/Money
    Money after_tax{ 41, 82, Currency::USD };
    Money before_tax{ 34, 56, Currency::USD };
    double tax{ (after_tax / before_tax) - 1 };
    cout << "A product with a final price of " << after_tax << " and a price"
        << " before taxes of " << before_tax << "\nhas been applied a "
        << tax * 100 << "% of taxes (" << after_tax - before_tax << ")\n";

    cout << "\nBye!\n";
    return 0;
}
catch (Money::DivisionByZero& e)
{
    cerr << "Money class: division by zero\n";
    return 1;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}