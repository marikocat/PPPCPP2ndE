#include "Window.h"
#include "Graph.h"

double one(double x) { return 1; }
double slope(double x) { return x / 2; }
double square(double x) { return x * x; }
double sloping_cos(double x) { return cos(x) + slope(x); }

int main()
try
{
	using namespace Graph_lib;

	const int xmax = 600;
	const int ymax = 600;

	const int xlength = xmax - 40;
	const int ylength = ymax - 40;

	const int x_orig = xmax / 2;
	const int y_orig = ymax / 2;
	const Point orig{ x_orig, y_orig };

	const int xscale = 20;
	const int yscale = 20;

	const int n_points = 400;
	const int r_min = -10;
	const int r_max = 11;

	Graph_lib::Window win{ Point{100, 100}, xmax, ymax, "Function graphs" };

	Axis x{ Axis::x, Point{20, y_orig}, xlength, xlength / xscale, "1 = = 20 pixels" };
	Axis y{ Axis::y, Point{x_orig, ymax - 20}, ylength, ylength / yscale, "1 = = 20 pixels" };
	x.set_color(Color::red);
	y.set_color(Color::red);

	Function f{ one, r_min, r_max, orig, n_points, xscale, yscale };
	f.set_color(Color::black);
	Function f2{ slope, r_min, r_max, orig, n_points, xscale, yscale };
	f2.set_color(Color::black);
	Function f3{ square, r_min, r_max, orig, n_points, xscale, yscale };
	f3.set_color(Color::black);
	Function f4{ cos, r_min, r_max, orig, n_points, xscale, yscale };
	f4.set_color(Color::blue);
	Function f5{ sloping_cos, r_min, r_max, orig, n_points, xscale, yscale };
	f5.set_color(Color::black);

	Text f2_label{ Point{f2.point(0).x, f2.point(0).y - 20}, "x/2" };
	f2_label.set_color(Color::black);

	win.attach(x);
	win.attach(y);
	win.attach(f);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);
	win.attach(f5);

	win.attach(f2_label);

	gui_main();
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