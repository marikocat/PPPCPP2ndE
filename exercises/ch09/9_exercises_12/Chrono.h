#pragma once

namespace Chrono {
	enum class Month {
		jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
	};

	int days_in_month(int y, Month m);

	Month operator++(Month& m);
	Month operator--(Month& m);

	enum class Day {
		sunday, monday, tuesday, wednesday, thursday, friday, saturday
	};

	Day operator+(const Day& d, int n);
	Day& operator+=(Day& d, int n);
	ostream& operator<<(ostream& os, const Day& d);

	constexpr int epoch_year{ 1970 };
	constexpr Day epoch_dow{ Day::thursday };

	class Date {
	public:
		class Invalid {};

		Date(int y, Month m, int d);
		Date(long int days);
		Date(); // default constructor
		// the default copy operations are fine

		// nonmodifying operations:
		int day() const;
		Month month() const;
		int year() const;
		long int get_days_since_epoch() const;

		// modifying operations:
		void add_day(int n);
		void add_month(int n);
		void add_year(int n);
	private:
		long int dse; // days since epoch
	};

	bool is_date(int y, Month m, int d); // true for valid date
	bool leapyear(int y); // true if y is a leap year
	long int days_since_epoch(int y, Month m, int d);
	
	Day day_of_week(const Date& d);
	Date next_workday(const Date& d);
	Date next_Sunday(const Date& d);
	int week_of_the_year(const Date& d);

	bool operator==(const Date& a, const Date& b);
	bool operator!=(const Date& a, const Date& b);
	bool operator<(const Date& a, const Date& b);
	bool operator<=(const Date& a, const Date& b);

	ostream& operator<<(ostream& os, const Date& d);
	istream& operator>>(istream& is, Date& dd);
}