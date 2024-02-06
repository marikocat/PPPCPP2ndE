#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Poly : public Polygon {
	public:
		Poly(initializer_list<Point> points);
	};

	Poly::Poly(initializer_list<Point> points)
	{
		for (Point p : points)
			add(p);
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1250, 800, "Tiled with hexagons" };

	Poly square{ {100, 100}, {200, 100}, {200, 200}, {100, 200} };
	square.set_color(Color::black);

	win.attach(square);
	win.wait_for_button();

	Poly not_a_square{ {100, 100}, {200, 200}, {200, 100}, {100, 200} };
	not_a_square.set_color(Color::black);

	win.attach(not_a_square);
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