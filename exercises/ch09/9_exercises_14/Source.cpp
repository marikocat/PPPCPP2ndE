#include "..\std_lib_facilities.h"

constexpr char currency{ '$' };

long int iround(double d)
{
	return (d < 0.0) ? (d - 0.5) : (d + 0.5);
}

class Money {
	long int amount_in_cents;
public:
	class DivisionByZero {};

	Money(long int d, long int c);
	Money(long int c);
	Money();

	long int get_amount_in_cents() const { return amount_in_cents; }

	long int get_dollars() const { return amount_in_cents / 100; }
	long int get_cents() const { return amount_in_cents % 100; }
};

Money::Money(long int d, long int c) : amount_in_cents{d * 100 + c} {}
Money::Money(long int c) : amount_in_cents{c} {}
Money::Money() : amount_in_cents{0} {}

Money operator-(const Money& m)
{
	return Money{ -m.get_amount_in_cents() };
}

Money operator+(const Money& m1, const Money& m2)
{
	return Money{ m1.get_amount_in_cents() + m2.get_amount_in_cents() };
}

Money operator-(const Money& m1, const Money& m2)
{
	return Money{ m1.get_amount_in_cents() - m2.get_amount_in_cents() };
}

Money operator*(const Money& m, double d)
{
	return Money{ iround(m.get_amount_in_cents() * d) };
}

Money operator*(double d, const Money& m)
{
	return Money{ iround(d * m.get_amount_in_cents()) };
}

Money operator/(const Money& m, double d)
{
	if (d == 0) throw Money::DivisionByZero{};

	return Money{ iround(m.get_amount_in_cents() / d) };
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
	os << currency << m.get_dollars() << '.';
	if (abs(m.get_cents()) < 10) os << '0';
	os << abs(m.get_cents());

	return os;
}

istream& operator>>(istream& is, Money& m)
{
	long int dollars{ 0 };
	char cur, dot;
	char c1, c2;

	is >> cur >> dollars >> dot >> c1 >> c2;
	if (!is) return is;
	if (cur != currency || dot != '.' || !isdigit(c1) || !isdigit(c2))
	{
		is.clear(ios_base::failbit);
		return is;
	}

	int cents{ (c1 - '0') * 10 + (c2 - '0') };

	if (dollars < 0) cents = -cents;
	m = Money{ dollars * 100 + cents };

	return is;
}

int main()
try {

    // Test Money*double, double*Money, Money/Money, Money/double, Money-Money
    // and <<
    Money budget{ 1000000,0 };
    Money wage{ 1500,0 };
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
    Money product{ 134,0 };
    double vat = 0.21;
    Money total{ product + (product * vat) };
    cout << "You have bought and paid by transference " << product
        << " for a product. But you forgot the VAT (" << vat * 100
        << "%).\n" << "With VAT applied the product costs " << total
        << " so you debt " << product - total << '\n';

    cout << '\n';

    // Test and justify Money/Money
    Money after_tax{ 41,82 };
    Money before_tax{ 34,56 };
    double tax{ (after_tax / before_tax) - 1 };
    cout << "A product with a final price of " << after_tax << " and a price"
        << " before taxes of " << before_tax << "\nhas been applied a "
        << tax * 100 << "% of taxes (" << after_tax - before_tax << ")\n";

    cout << '\n';

    // Test >> and << operators;
    cout << "Write some quantities (examples: $123.04 or $-10.10, two digits"
        << " for cents are mandatory. Quit with Ctrl+D).\n> ";
    Money input{ 0 };
    while (cin) {
        cin >> input;
        if (cin.eof()) break;
        if (cin.fail()) {
            cout << "Bad input format\n> ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            cout << '\t' << input << "\n> ";
        }
    }

    cout << "\nBye!\n";

    // Forced errors (division by zero)
    //cout << Money{}/0;
    //cout << Money{}/Money{};
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