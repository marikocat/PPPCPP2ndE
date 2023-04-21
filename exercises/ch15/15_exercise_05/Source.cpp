#include "Simple_window.h"
#include "Graph.h"

double term(double x) { return pow(-1, x) / (2 * x + 1); }

double leib_f(double n)
{
	double sum = 0;
	for (int i = 0; i < n; ++i) sum += term(i);
	return sum;
}

int exp_num_of_terms = 10;

double fct(double)
{
	return leib_f(exp_num_of_terms);
}

int main()
try
{
	using namespace Graph_lib;

	const Point orig{ 300, 300 };
	const int xscale = 20;
	const int yscale = 20;

	Simple_window win{ Point{100, 100}, 600, 600, "Leibniz’s series" };

	Axis x{ Axis::x, Point{0, orig.y}, win.x_max(), win.x_max() / xscale, "x axis" };
	Axis y{ Axis::y, Point{orig.x, win.y_max()}, win.y_max(), win.y_max() / yscale, "y axis" };
	x.label.move(-150, 0);
	y.label.move(20, 20);
	x.set_color(Color::red);
	y.set_color(Color::red);

	win.attach(x);
	win.attach(y);

	for (int n = 0; n < 50; ++n)
	{
		ostringstream ss;
		ss << "Leibniz's formula aproximation; n == " << n;
		win.set_label(ss.str());
		exp_num_of_terms = n;
		Function lf{ fct, -10, 10, orig, 200, xscale, yscale };
		lf.set_color(Color::black);
		win.attach(lf);
		win.wait_for_button();
		win.detach(lf);
	}
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}