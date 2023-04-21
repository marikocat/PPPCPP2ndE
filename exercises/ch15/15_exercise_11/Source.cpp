#include "Simple_window.h"
#include "Graph.h"

struct Temp_data {
	int month;
	int temp;
};

istream& operator>>(istream& is, Temp_data& td)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Temp_data t_d;

	if (is >> ch1 >> t_d.month >> ch2 >> t_d.temp >> ch3)
	{
		if (ch1 != '(' || ch2 != ',' || ch3 != ')')
		{
			is.clear(ios_base::failbit);
			return is;
		}
	}
	else
	{
		if (ch1 == ';')
		{
			is.clear();
			is.putback(ch1);
			is.clear(ios_base::failbit);
			return is;
		}
		return is;
	}

	td = t_d;
	return is;
}

void end_of_loop(istream& is, char term, const string& message)
{
	if (is.eof()) return;
	if (is.fail())
	{
		is.clear();
		char ch;
		if (is >> ch && ch == term) return;
		error(message);
	}
}

class Scale {
	int cbase;
	int vbase;
	double scale;
public:
	Scale(int cb, int vb, double s) : cbase{ cb }, vbase{ vb }, scale{ s } {}
	int operator()(int v) const { return cbase + (v - vbase) * scale; }
};

string value_to_string(double v)
{
	ostringstream oss;
	oss << v;
	return oss.str();
}

const vector<string> months = {
	"January", "February", "March", "April", "May", "June", "July", "August",
	"September", "October", "November", "December"
};

int main()
try
{
	const int xmax = 1300;
	const int ymax = 800;

	const int xoffset = 100;
	const int yoffset = 100;

	const int xspace = 100;
	const int yspace = 100;

	const int xlength = xmax - xoffset - xspace;
	const int ylength = ymax - yoffset - yspace;

	const int base_month = 1;
	const int end_month = 12;
	const int month_gap = 1;

	const int base_temp = 0;
	const int max_temp = 50;
	const int temp_gap = 10;

	const double xscale = double(xlength) / (end_month - base_month);
	const double yscale = double(ylength) / (max_temp - base_temp);

	Scale xs{ xoffset, base_month, xscale };
	Scale ys{ ymax - yoffset, base_temp, -yscale };

	Simple_window win{ Point{100, 100}, xmax, ymax, "Average High Temps" };

	Axis x{ Axis::x, Point{xoffset, ymax - yoffset}, xlength, (end_month - base_month) / month_gap, "months" };
	x.label.move(250, 40);
	x.set_color(Color::dark_red);
	Axis y{ Axis::y, Point{xoffset, ymax - yoffset}, ylength, (max_temp - base_temp) / temp_gap, "temperatures, c" };
	y.label.move(20, -20);
	y.set_color(Color::dark_red);

	Vector_ref<Text> x_labels;
	for (int i = base_month / month_gap; i <= end_month / month_gap; ++i)
	{
		x_labels.push_back(new Text{ Point{xs(i * month_gap), ymax - yoffset + 20}, months[i - 1] });
		x_labels[x_labels.size() - 1].set_color(Color::dark_red);
		win.attach(x_labels[x_labels.size() - 1]);
	}
	Vector_ref<Text> y_labels;
	for (int i = base_temp / temp_gap; i <= max_temp / temp_gap; ++i)
	{
		y_labels.push_back(new Text{ Point{xoffset - 40, ys(i * temp_gap)}, value_to_string(i * temp_gap) });
		y_labels[y_labels.size() - 1].set_color(Color::dark_red);
		win.attach(y_labels[y_labels.size() - 1]);
	}

	string file_name = "data.txt";
	ifstream ifs(file_name);
	if (!ifs) error("can't open ", file_name);

	Temp_data temp_d;
	Marked_polyline city1{ "o" };
	while (ifs >> temp_d)
	{
		city1.add(Point{ xs(temp_d.month), ys(temp_d.temp) });
	}
	city1.set_color(Color::dark_blue);
	end_of_loop(ifs, ';', "bad termination for a city");
	Text c1_l{ city1.point(6), "First city" };
	c1_l.move(10, -20);
	c1_l.set_color(Color::dark_blue);

	Marked_polyline city2{ "x" };
	while (ifs >> temp_d)
	{
		city2.add(Point{ xs(temp_d.month), ys(temp_d.temp) });
	}
	city2.set_color(Color::dark_green);
	Text c2_l{ city2.point(6), "Secong city" };
	c2_l.move(10, -20);
	c2_l.set_color(Color::dark_green);

	win.attach(x);
	win.attach(y);
	win.attach(city1);
	win.attach(city2);
	win.attach(c1_l);
	win.attach(c2_l);
	win.wait_for_button();
}
catch (exception& e)
{
	cout << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}