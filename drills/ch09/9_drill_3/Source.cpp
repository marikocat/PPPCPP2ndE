#include "..\std_lib_facilities.h"

class Date {
public:
	class Invalid {};
	Date(int y, int m, int d);
	void add_day(int n);
	int month() const;
	int day() const;
	int year() const;
private:
	int y, m, d;
	bool is_valid();
};

bool Date::is_valid()
{
	if (d < 1 || d > 31) return false;
	if (m < 1 || m > 12) return false;
	return true;
}

bool is_date(int y, int m, int d)
{
	// assume that y is valid
	if (d < 1 || d > 31) return false;
	if (m < 1 || m > 12) return false;
	return true;
}

Date::Date(int yy, int mm, int dd) :y{yy}, m{mm}, d{dd}
{
	//if (!is_valid()) throw Invalid{};
	if (!is_date(yy, mm, dd)) error("invalid date");
}

void Date::add_day(int n)
{
	// increase dd by n days
	d += n;

	while (d > 31) { ++m; d -= 31; }
	while (d < 1) { --m; d += 31; }
	while (m > 12) { ++y; m -= 12; }
	while (m < 1) { --y; m += 12; }
}

int Date::day() const
{
	return d;
}

int Date::month() const
{
	return m;
}

int Date::year() const
{
	return y;
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
		Date today{ 2005, 6, 25 };

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