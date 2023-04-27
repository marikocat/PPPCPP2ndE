#include "..\std_lib_facilities.h"
#include "Chrono.h"

namespace Chrono {
	// member function definitions:

	Date::Date(int yy, Month mm, int dd)
		: y{ yy }, m{ mm }, d{ dd }
	{
		if (!is_date(yy, mm, dd)) throw Invalid();
	}

	const Date& default_date()
	{
		static Date dd{ 2001, Month::jan, 1 };
		return dd;
	}

	Date::Date()
		: y{ default_date().year() },
		m{ default_date().month() },
		d{ default_date().day() }
	{
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
		// ...
		d += n;

		while (d > days_in_month(y, m)) {
			d -= days_in_month(y, m);
			++m;
			if (m == Month::jan) ++y;
		}
		while (d < 1) {
			d += days_in_month(y, m);
			--m;
			if (m == Month::dec) --y;
		}
	}

	void Date::add_month(int n)
	{
		// ...
		if (n < 0)
		{
			for (int i = 0; i < n; i++) {
				--m;
				if (m == Month::dec) --y;
			}
		}
		else if (n > 0)
		{
			for (int i = 0; i < n; i++) {
				++m;
				if (m == Month::jan) ++y;
			}
		}
	}

	void Date::add_year(int n)
	{
		if (m == Month::feb && d == 29 && !leapyear(y + n)) {
			m = Month::mar;
			d = 1;
		}
		y += n;
	}

	// helper functions:

	int days_in_month(int y, Month m)
	{
		int days_in_month = 31; // most months have 31 days
		switch (m) {
		case Month::feb:
			days_in_month = (leapyear(y)) ? 29 : 28;
			break;
		case Month::apr: case Month::jun: case Month::sep: case Month::nov:
			days_in_month = 30;
			break;
		}
		return days_in_month;
	}

	bool is_date(int y, Month m, int d)
	{
		// assume that y is valid

		if (d <= 0) return false;
		if (m < Month::jan || m > Month::dec) return false;
		if (days_in_month(y, m) < d) return false;

		return true;
	}

	bool leapyear(int y)
	{
		return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
	}

	bool operator==(const Date& a, const Date& b)
	{
		return a.year() == b.year()
			&& a.month() == b.month()
			&& a.day() == b.day();
	}

	bool operator!=(const Date& a, const Date& b)
	{
		return !(a == b);
	}

	ostream& operator<<(ostream& os, const Date& d)
	{
		return os << '(' << d.year() << ',' << int(d.month()) << ',' << d.day() << ')';
	}

	istream& operator>>(istream& is, Date& dd)
	{
		int y, m, d;
		char ch1, ch2, ch3, ch4;
		is >> ch1 >> y >> ch2 >> m >> ch3 >> d >> ch4;
		if (!is) return is;
		if (ch1 != '(' || ch2 != ',' || ch3 != ',' || ch4 != ')') { // format error
			is.clear(ios_base::failbit); // set the fail bit
			return is;
		}

		dd = Date(y, Month(m), d);

		return is;
	}

	

	Day day_of_week(const Date& d)
	{
		// ...
		return Day::friday;
	}

	Date next_Sunday(const Date& d)
	{
		// ...
		return default_date();
	}

	Date next_weekday(const Date& d)
	{
		// ...
		return default_date();
	}
}