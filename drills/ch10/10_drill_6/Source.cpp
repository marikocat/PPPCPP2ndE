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
	: x{ x }, y{ y }
{

}

Point::Point()
	: x{ 0 }, y{ 0 }
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

constexpr int points_number{ 7 };
const string file_name = "mydata.txt";

void get_points(istream& is, vector<Point>& points, int size)
{
	
	for (Point p; is >> p;) {
		if (is) {
			points.push_back(p);
		}
		else {
			cout << "Not a point!\n";
			is.clear();
			is.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		if (size != 0 && points.size() >= size) break;
	}
}

int main()
{
	try {
		vector<Point> original_points;

		cout << "Enter " << points_number
			<< " points as pairs of coordinates with format (x,y):\n";
		get_points(cin, original_points, points_number);

		cout << "You've entered those points:\n" << original_points;

		cout << "Writing to a file " << file_name << "\n";
		ofstream ost{ file_name };
		if (!ost) error("can't open output file ", file_name);
		ost << original_points;
		ost.close();

		cout << "Reading points from a file " << file_name << "\n";
		vector<Point> processed_points;
		ifstream ist{ file_name };
		if (!ist) error("can't open input file ", file_name);
		get_points(ist, processed_points, 0);
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