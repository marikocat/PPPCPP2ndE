#include "..\std_lib_facilities.h"
#include "Chrono.h"

namespace Chrono {
	// Day operator definitions
	Day operator+(const Day& d, int n)
	{
		int sum = int(d) + n;
		sum %= 7;
		return Day(sum);
	}

	Day& operator+=(Day& d, int n)
	{
		d = d + n;
		return d;
	}

	ostream& operator<<(ostream& os, const Day& d)
	{
		switch (d) {
		case Day::sunday:    os << "sunday"; break;
		case Day::monday:    os << "monday"; break;
		case Day::tuesday:   os << "tuesday"; break;
		case Day::wednesday: os << "wednesday"; break;
		case Day::thursday:  os << "thursday"; break;
		case Day::friday:    os << "friday"; break;
		case Day::saturday:  os << "saturday"; break;
		default: error("Day output: invalid day");
		}

		return os;
	}

	// Date member function definitions:
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

	bool operator<(const Date& a, const Date& b)
	{
		if (a.year() != b.year()) return (a.year() < b.year());
		if (a.month() != b.month()) return (a.month() < b.month());
		return (a.day() < b.day());
	}

	bool operator<=(const Date& a, const Date& b)
	{
		return ((a < b) || (a == b));
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

	Date next_workday(const Date& d)
	{
		Day dow{ day_of_week(d) };
		Date wd{ d };

		wd.add_day(1);
		if (dow == Day::saturday) wd.add_day(1);
		if (dow == Day::friday) wd.add_day(2);
		
		return wd;
	}

	int week_of_the_year(const Date& d)
	{
		Date wd{ Date{d.year(), Month::jan, 1} };
		int week{ 1 };

		wd = next_Sunday(wd);
		while (wd <= d)
		{
			wd = next_Sunday(wd);
			++week;
		}

		return week;
	}

	Day day_of_week(const Date& d)
	{
		int y{ d.year() };
		Day dow{ epoch_dow };

		for (int i = epoch_year; i < y; ++i)
		{
			if (leapyear(i)) dow += 366;
			else dow += 365;
		}

		Month m{ d.month() };
		for (Month i = Month::jan; i < m; ++i)
			dow += days_in_month(y, i);

		dow += (d.day() - 1);

		return dow;
	}

	Date next_Sunday(const Date& d)
	{
		Day dow{ day_of_week(d) };
		Date ns{ d };
		ns.add_day(7 - int(dow));
		return ns;
	}
}