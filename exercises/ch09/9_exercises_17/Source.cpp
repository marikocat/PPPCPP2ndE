#include "..\std_lib_facilities.h"
#include "Math.h"
using namespace Math;

long int iround(double d)
{
    return (d < 0.0) ? (d - 0.5) : (d + 0.5);
}

enum class Currency {
    USD, EUR, GBP
};

const vector<string> currencies = { "USD", "EUR", "GBP" };

ostream& operator<<(ostream& os, const Currency currency)
{
    os << currencies[int(currency)];
    return os;
}

istream& operator>>(istream& is, Currency& currency)
{
    char c;
    string name;
    // assume currency name has always three chars
    // beware the magic number!
    for (int i = 0; i < 3; ++i) {
        is >> c;
        if (!is) return is;  // in case of EOF
        name += c;
    }

    for (int i = 0; i < currencies.size(); ++i)
    {
        if (currencies[i] == name)
        {
            currency = Currency(i);
            return is;
        }
    }
    error("invalid currency");
}

class Money {
    long int amount_in_cents;
    Currency currency;
public:
    class DivisionByZero {};

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
    : amount_in_cents{ d * 100 + c }, currency{ cur }
{
}

Money::Money(long int a, Currency cur)
    : amount_in_cents{ a }, currency{ cur }
{
}

Money::Money(double a, Currency cur)
    : amount_in_cents{ (long int)(a * 100) }, currency{ cur }
{

}

Money::Money() : amount_in_cents{ 0 }, currency{ Currency::USD }
{
}

Money operator-(const Money& m)
{
    return Money{ -m.get_amount_in_cents(), m.get_currency() };
}

Money operator+(const Money& m1, const Money& m2)
{
    return Money{ m1.get_amount_in_cents() + m2.get_amount_in_cents(), m1.get_currency() };
}

Money operator-(const Money& m1, const Money& m2)
{
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
    if (m2.get_amount_in_cents() == 0) throw Money::DivisionByZero{};

    return double(m1.get_amount_in_cents()) / m2.get_amount_in_cents();
}

bool operator==(const Money& m1, const Money& m2)
{
    return (m1.get_amount_in_cents() == m2.get_amount_in_cents());
}

bool operator!=(const Money& m1, const Money& m2)
{
    return !(m1 == m2);
}

ostream& operator<<(ostream& os, const Money& m)
{
    os << m.get_currency() << m.get_dollars() << '.';
    if (abs(m.get_cents()) < 10) os << '0';
    os << abs(m.get_cents());

    return os;
}

istream& operator>>(istream& is, Money& m)
{
    double amount{ 0 };
    Currency currency{ Currency::USD };

    is >> currency;
    if (!is) return is;
    is >> amount;
    if (!is) return is;

    m = Money{ amount, currency };

    return is;
}

int main()
try
{
    Rational r{ 456,100 };
    Money m1(456, 0, Currency::USD);
    Money m2(100, 0, Currency::USD);

    cout << std::fixed << std::setprecision(20)
        << (r * 100).convert_to_double() << '\n';
    cout << std::fixed << std::setprecision(12)
        << m1 / m2 * 100 << '\n';

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