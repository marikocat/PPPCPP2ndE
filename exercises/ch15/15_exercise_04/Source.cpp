#include "Simple_window.h"
#include "Graph.h"

int main()
try
{
	using namespace Graph_lib;

	const Point orig{ 300, 300 };
	const int xscale = 20;
	const int yscale = 20;

	Simple_window win{ Point{100, 100}, 600, 600, "Functions" };

	Axis x{ Axis::x, Point{0, orig.y}, win.x_max(), win.x_max() / xscale, "x axis" };
	Axis y{ Axis::y, Point{orig.x, win.y_max()}, win.y_max(), win.y_max() / yscale, "y axis" };
	x.label.move(-150, 0);
	y.label.move(20, 20);
	x.set_color(Color::red);
	y.set_color(Color::red);

	Function f1{ sin, -10, 10, orig, 200, xscale, yscale };
	f1.set_color(Color::black);
	Text l1{ Point{f1.point(0).x, f1.point(0).y}, "cos()" };
	l1.set_color(Color::black);

	Function f2{ cos, -10, 10, orig, 200, xscale, yscale };
	f2.set_color(Color::blue);
	Text l2{ Point{f2.point(0).x, f2.point(0).y}, "sin()" };
	l2.set_color(Color::blue);
	l2.move(0, 15);

	Function f3{ [](double x) { return sin(x) + cos(x); }, -15, 15, orig, 200, xscale, yscale };
	f3.set_color(Color::dark_cyan);
	Text l3{ Point{f3.point(0).x, f3.point(0).y}, "sin(x) + cos(x)" };
	l3.set_color(Color::dark_cyan);
	l3.move(5, 20);

	Function f4{ [](double x) {return sin(x) * sin(x) + cos(x) * cos(x); }, -15, 15, orig, 200, xscale, yscale };
	f4.set_color(Color::green);
	Text l4{ Point{f4.point(0).x, f4.point(0).y}, "cos(x) * cos(x) + sin(x) * sin(x)" };
	l4.set_color(Color::green);
	l4.move(5, -20);

	win.attach(x);
	win.attach(y);
	win.attach(f1);
	win.attach(f2);
	win.attach(f3);
	win.attach(f4);
	win.attach(l1);
	win.attach(l2);
	win.attach(l3);
	win.attach(l4);

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