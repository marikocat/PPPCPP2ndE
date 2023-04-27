#include "..\std_lib_facilities.h"

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	class Invalid {};
	Date(int y, Month m, int d);
	void add_day(int n);
	Month month() const;
	int day() const;
	int year() const;
private:
	Month m;
	int y, d;
	bool is_valid();
};

bool Date::is_valid()
{
	if (d < 1 || d > 31) return false;
	if (m < Month::jan || m > Month::dec) return false;
	return true;
}

Date::Date(int yy, Month mm, int dd) :y{ yy }, m{ mm }, d{ dd }
{
	if (!is_valid()) throw Invalid{};
}

Month operator++(Month& m)
{
	m = (m == Month::dec) ? Month::jan : Month(int(m) + 1);
	return m;
}

Month operator--(Month& m)
{
	m = (m == Month::jan) ? Month::dec : Month(int(m) - 1);
	return m;
}

void Date::add_day(int n)
{
	// increase dd by n days
	d += n;

	while (d > 31) { 
		++m;
		d -= 31;
		if (m == Month::jan) ++y;
	}
	while (d < 1) { 
		--m; 
		d += 31;
		if (m == Month::dec) --y;
	}
}

int Date::day() const
{
	return d;
}

Month Date::month() const
{
	return m;
}

int Date::year() const
{
	return y;
}

ostream& operator<<(ostream& os, Month m)
{
	return os << int(m);
}

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.year()
		<< ',' << d.month()
		<< ',' << d.day() << ')';
}

int main()
{
	try
	{
		Date today{ 2005, Month::jun, 25 };

		Date tomorrow = today;
		tomorrow.add_day(633);
		Date next{ today };
		next.add_day(2);

		cout << "today: " << today << "\n";
		cout << "tomorrow: " << tomorrow << "\n";
		cout << "next: " << next << "\n";
		// vector<Date> dates(5); error - no default constructor
	}
	catch (exception& e) {
		cout << e.what() << "\n";
	}
	catch (Date::Invalid& ex) {
		cout << "invalid date exception\n";
	}
}