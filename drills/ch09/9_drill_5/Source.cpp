#include "..\std_lib_facilities.h"

enum class Month {
	jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
};

class Date {
public:
	class Invalid {};
	Date();
	Date(int y);
	Date(int y, Month m, int d);

	void add_day(int n);
	void add_month(int n);
	void add_year(int n);

	Month month() const;
	int day() const;
	int year() const;
private:
	Month m;
	int y, d;
	bool is_valid();
	// Instead of placing the default values for members in the constructor, we could place them on the members themselves
	// An initializer for a class member specified as part of the member declaration is called an in-class initializer.
	//int y {2001};
	//Month m{ Month::jan };
	//int d{ 1 };
};

bool Date::is_valid()
{
	if (d < 1 || d > 31) return false;
	if (m < Month::jan || m > Month::dec) return false;
	return true;
}

const Date& default_value()
{
	static Date dd{ 2001, Month::jan, 1 };
	return dd;
}

Date::Date()
	:y{default_value().year()},
	m{default_value().month()},
	d{default_value().day()}
{
	if (!is_valid()) throw Invalid{};
}

Date::Date(int yy)
	:y{yy},
	m{ default_value().month() },
	d{ default_value().day() }
{
	if (!is_valid()) throw Invalid{};
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

void Date::add_month(int n)
{
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
	if (n < 0)
	{
		for (int i = 0; i < n; i++) {
			--y;
		}
	}
	else if (n > 0)
	{
		for (int i = 0; i < n; i++) {
			++y;
		}
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

		Date tomorrow = today; // copy today as initializer
		tomorrow.add_day(633);
		Date next{ today };
		next.add_day(2);

		cout << "today: " << today << "\n";
		cout << "tomorrow: " << tomorrow << "\n";
		cout << "next: " << next << "\n";

		vector<Date> dates(5); // if no default constructor - error
		vector<Date> dates2(5, default_value()); // explicit, if we don't have default constructor

		tomorrow = today; // copy today as a right-hand side of an assignment
		cout << "tomorrow: " << tomorrow << "\n";
		tomorrow.add_year(20);
		tomorrow.add_month(15);
		cout << "tomorrow: " << tomorrow << "\n";

		int x = int{};
		cout << x << "\n";
		double d = double{};
		cout << d << "\n";

		const Date date{ 2005 };
		cout << date.day() << "\n";
	}
	catch (exception& e) {
		cout << e.what() << "\n";
	}
	catch (Date::Invalid& ex) {
		cout << "invalid date exception\n";
	}
}