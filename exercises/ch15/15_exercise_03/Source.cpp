#include "Simple_window.h"
#include "Graph.h"

// need to do this later, when I get to templates

namespace Graph_lib {
	class Func : public Shape {
	public:
		Func(Fct fct, double range1, double range2, Point orig, int count = 100, double xscale = 25, double yscale = 25);

		void reset(Fct fct, double range1, double range2, Point orig, double xscale, double yscale);
		void reset_func(Fct fct) { reset(fct, r1, r2, o, xs, ys); }
		void reset_range(double range1, double range2) { reset(f, range1, range2, o, xs, ys); }
		void reset_origin(Point orig) { reset(f, r1, r2, orig, xs, ys); }
		void reset_scale(double xscale, double yscale) { reset(f, r1, r2, o, xscale, yscale); }
	private:
		Fct* f;
		double r1;
		double r2;
		Point o;
		int c;
		double xs;
		double ys;
	};

	Func::Func(Fct fct, double range1, double range2, Point orig, int count, double xscale, double yscale)
		: c{ count } // cannot change number of points, because points are private in Shape
	{
		reset(fct, range1, range2, orig, xscale, yscale);
	}

	void Func::reset(Fct fct, double range1, double range2, Point orig, double xscale, double yscale)
	{
		f = fct;
		r1 = range1;
		r2 = range2;
		o = orig;
		xs = xscale;
		ys = yscale;

		if (r2 - r1 <= 0) error("bad graphing range");
		if (c <= 0) error("non-positive graphing count");
		double dist = (r2 - r1) / c;
		double r = r1;

		if (number_of_points() == 0)
			for (int i = 0; i < c; ++i) {
				add(Point(o.x + int(r * xscale), o.y - int(f(r) * yscale)));
				r += dist;
			}
		else
			for (int i = 0; i < c; ++i)
			{
				set_point(i, Point(o.x + int(r * xscale), o.y - int(f(r) * yscale)));
				r += dist;
			}
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 600, "Function reset" };

	const Point orig{ 300, 300 };

	Axis x{ Axis::x, Point{0, orig.y}, 600, 30, "x axis" };
	Axis y{ Axis::y, Point{orig.x, 600}, 600, 30, "y axis" };
	x.label.move(-150, 0);
	y.label.move(20, 20);
	x.set_color(Color::red);
	y.set_color(Color::red);

	Func func{ cos, -10, 10, orig, 200, 20, 20 };
	func.set_color(Color::black);

	win.attach(x);
	win.attach(y);
	win.attach(func);
	win.wait_for_button();

	func.reset_func(sin);
	func.reset_range(-5, 5);
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