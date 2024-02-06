#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Ellipse" };

	Graph_lib::Ellipse ellipse{ Point{200, 400}, 150, 100 };
	ellipse.set_color(Color::black);

	Axis ax{ Axis::x, Point{ellipse.center().x, ellipse.center().y}, 400, 4 };
	ax.set_color(Color::red);

	Axis ay{ Axis::y, Point{ellipse.center().x, ellipse.center().y}, 300, 3 };
	ay.set_color(Color::red);

	Mark f1{ ellipse.focus1(), '+' };
	Mark f2{ ellipse.focus2(), '+' };

	Point pointOnEllipse{ ellipse.center().x + int(ellipse.major() * cos(30 * pi / 180)),
		ellipse.center().y - int(ellipse.minor() * sin(30 * pi / 180))};
	Mark pm{ pointOnEllipse, 'x' };

	Line l1{ ellipse.focus1(), pointOnEllipse };
	l1.set_color(Color::black);
	Line l2{ ellipse.focus2(), pointOnEllipse };
	l2.set_color(Color::black);

	win.attach(ellipse);
	win.attach(ax);
	win.attach(ay);
	win.attach(f1);
	win.attach(f2);
	win.attach(pm);
	win.attach(l1);
	win.attach(l2);
	win.wait_for_button();
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}