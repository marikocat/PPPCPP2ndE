#include "..\std_lib_facilities.h"

class Point {
public:
	Point(double x, double y);
	Point();
	double get_x() const { return x; }
	double get_y() const { return y; }
private:
	double x;
	double y;
};

Point::Point(double x, double y)
	: x{x}, y{y}
{

}

Point::Point()
	: x{0}, y{0}
{

}

istream& operator>>(istream& is, Point& p)
{
	double n1, n2;
	char ch1, ch2, ch3;
	is >> ch1 >> n1 >> ch2 >> n2 >> ch3;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ',' || ch3 != ')') {
		is.clear(ios_base::failbit);
		return is;
	}

	p = Point{ n1, n2 };

	return is;
}

ostream& operator<<(ostream& os, const vector<Point>& vp)
{
	for (const Point& p : vp)
		os << '(' << p.get_x() << ',' << p.get_y() << ')' << '\n';

	return os;
}

constexpr int points_number{ 3 };
const string file_name = "mydata.txt";

void fill_from_file(vector<Point>& points)
{
	ifstream ist{ file_name };
	if (!ist) error("can't open input file ", file_name);

	for (Point p; ist >> p;) {
		points.push_back(p);
	}
}

void write_to_file(const vector<Point>& points)
{
	ofstream ost{ file_name };
	if (!ost) error("can't open output file ", file_name);
	ost << points;
	// When a file stream goes out of scope its associated file is closed. When a file is closed its associated buffer is “flushed”; that
	// is, the characters from the buffer are written to the file.
}

int main()
{
	try {
		vector<Point> original_points;

		cout << "Enter " << points_number 
			<< " points as pairs of coordinates with format (x,y):\n";
		while (original_points.size() < points_number) {
			Point p;
			if (cin >> p) {
				original_points.push_back(p);
			}
			else {
				cout << "That's not a point!\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
		}

		cout << "You've entered those points:\n" << original_points;

		cout << "Writing to a file " << file_name << "\n";
		write_to_file(original_points);

		cout << "Reading points from a file " << file_name << "\n";
		vector<Point> processed_points;
		fill_from_file(processed_points);
		cout << processed_points;

		return 0;
	}
	catch (exception& e) {
		cerr << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Unknown exception!\n";
		return 2;
	}
}