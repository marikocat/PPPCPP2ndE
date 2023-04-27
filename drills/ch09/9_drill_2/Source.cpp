#include "..\std_lib_facilities.h"

struct Date {
	int y, m, d;
	Date(int y, int m, int d); // check for valid date and initialize
	void add_day(int n);
};

bool is_date(int y, int m, int d)
{
	// assume that y is valid
	if (d < 1 || d > 31) return false;
	if (m < 1 || m > 12) return false;
	return true;
}

Date::Date(int yy, int mm, int dd)
{
	if (!is_date(yy, mm, dd)) error("invalid date");
	y = yy;
	m = mm;
	d = dd;
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

ostream& operator<<(ostream& os, const Date& d)
{
	return os << '(' << d.y
		<< ',' << d.m
		<< ',' << d.d << ')';
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
	}
	catch (exception& e) {
		cout << e.what() << "\n";
	}
}