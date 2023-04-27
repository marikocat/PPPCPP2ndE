#include "..\std_lib_facilities.h"

struct Date {
	int y;
	int m;
	int d;
};

bool is_date(int y, int m, int d)
{
	// assume that y is valid
	if (d < 1 || d > 31) return false;
	if (m < 1 || m > 12) return false;
	return true;
}

// helper functions
void init_day(Date& dd, int y, int m, int d)
{
	// check that (y, m, d) is a valid date
	if (!is_date(y, m, d)) error("not valid date");
	dd.y = y;
	dd.m = m;
	dd.d = d;
}

void add_day(Date& dd, int n)
{
	// increase dd by n days
	dd.d += n;

	while (dd.d > 31) { ++dd.m; dd.d -= 31; }
	while (dd.d < 1) { --dd.m; dd.d += 31; }
	while (dd.m > 12) { ++dd.y; dd.m -= 12; }
	while (dd.m < 1) { --dd.y; dd.m += 12; }
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
		Date today;
		init_day(today, 2005, 6, 25);

		Date tomorrow = today;
		add_day(tomorrow, 633);

		cout << "today: " << today << "\n";
		cout << "tomorrow: " << tomorrow << "\n";
	}
	catch (exception& e) {
		cout << e.what() << "\n";
	}
}