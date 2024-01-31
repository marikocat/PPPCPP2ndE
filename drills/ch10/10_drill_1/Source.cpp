#include "..\std_lib_facilities.h"

const string oname = "mydata.txt";

struct Point {
	double x;
	double y;
};

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
	p.x = n1;
	p.y = n2;
	return is;
}

ostream& operator<<(ostream& os, vector<Point>& vp)
{
	for (Point& p : vp)
		os << '(' << p.x << ',' << p.y << ')' << '\n';
	return os;
}

int main()
{
	cout << "Please enter input file name: ";
	string iname;
	cin >> iname;
	ifstream ist{ iname };
	if (!ist) error("can't open input file ", iname);

	vector<Point> original_points;
	for (int i = 0; i < 7; ++i) {
		Point p;
		ist >> p;
		if (ist.fail()) {
			cout << "invalid input file\n";
			break;
		}
		original_points.push_back(p);
	}

	
	ofstream ost{ oname };
	if (!ost) error("can't open output file ", oname);

	ost << original_points;
	cout << original_points;
}