#include "Simple_window.h"
#include "Graph.h"

struct Mark_data {
	string country;
	double population;
	double gdp;
};

istream& operator>>(istream& is, Mark_data& md)
{
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;
	Mark_data m_d;

	if (is >> ch1 >> m_d.country >> ch2 >> m_d.population >> m_d.gdp >> ch3)
	{
		if (ch1 != '(' || ch2 != ':' || ch3 != ')') {
			is.clear(ios_base::failbit);
			cout << "failbit\n";
			return is;
		}
	}
	else
		return is;

	md = m_d;
	return is;
}

class Scale {
	int cbase;
	int vbase;
	double scale;
public:
	Scale(int cb, int vb, double s) : cbase{cb}, vbase{vb}, scale{s} {}
	int operator()(int v) const { return cbase + (v - vbase) * scale; }
};

string value_to_string(double v)
{
	ostringstream oss;
	oss << v;
	return oss.str();
}

int main()
try
{
	const int xmax = 800;
	const int ymax = 800;

	const int xoffset = 100;
	const int yoffset = 100;

	const int xspace = 100;
	const int yspace = 100;

	const int xlength = xmax - xoffset - xspace;
	const int ylength = ymax - yoffset - yspace;

	const int base_population = 0;
	const int max_population = 1500;

	const int base_gdp = 10000;
	const int max_gdp = 70000;

	const int population_gap = 500;
	const int gdp_gap = 10000;

	const double xscale = double(xlength) / (max_population - base_population);
	const double yscale = double(ylength) / (max_gdp - base_gdp);

	Scale xs(xoffset, base_population, xscale);
	Scale ys(ymax - yoffset, base_gdp, -yscale);

	Simple_window win{ Point{100, 100}, xmax, ymax, "GDP per person vs population of country" };

	Axis x{ Axis::x, Point{xoffset, ymax - yoffset}, xlength, (max_population - base_population) / population_gap, "population, mln" };
	x.label.move(150, 40);
	x.set_color(Color::dark_red);
	Axis y{ Axis::y, Point{xoffset, ymax - yoffset}, ylength, (max_gdp - base_gdp) / gdp_gap, "GDP per person, $" };
	y.label.move(0, -40);
	y.set_color(Color::dark_red);

	Vector_ref<Text> x_labels;
	for (int i = base_population / population_gap; i <= max_population / population_gap; ++i)
	{
		x_labels.push_back(new Text{ Point{xs(i * population_gap), ymax - yoffset + 20}, value_to_string(i * population_gap) });
		x_labels[x_labels.size() - 1].set_color(Color::dark_red);
		win.attach(x_labels[x_labels.size() - 1]);
	}
	Vector_ref<Text> y_labels;
	for (int i = base_gdp / gdp_gap; i <= max_gdp / gdp_gap; ++i)
	{
		y_labels.push_back(new Text{ Point{xoffset / 2, ys(i * gdp_gap)}, value_to_string(i * gdp_gap) });
		y_labels[y_labels.size() - 1].set_color(Color::dark_red);
		win.attach(y_labels[y_labels.size() - 1]);
	}

	string file_name = "data.txt";
	ifstream ifs{ file_name };
	if (!ifs) error("can't open ", file_name);

	Marks marks{ "x" };
	Vector_ref<Text> mark_labels;
	Mark_data d;
	while (ifs >> d)
	{
		marks.add(Point{ xs(d.population), ys(d.gdp) });
		mark_labels.push_back(new Text{ Point{marks.point(marks.number_of_points() - 1).x, 
			marks.point(marks.number_of_points() - 1).y},
			d.country });
		mark_labels[mark_labels.size() - 1].set_color(Color::blue);
		cout << d.country << "\n";
		win.attach(mark_labels[mark_labels.size() - 1]);
	}

	win.attach(x);
	win.attach(y);
	win.attach(marks);
	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}