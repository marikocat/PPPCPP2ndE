#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	class Regular_polygon : public Graph_lib::Polygon {
	public:
		Regular_polygon(Point center, int sidesNumber, int distance);

		Point center() const { return c; }
		int radius() const { return d; }
	private:
		Point c;
		int sNum;
		int d;
	};

	Regular_polygon::Regular_polygon(Point center, int sidesNumber, int distance)
		:c{ center }, sNum{ sidesNumber }, d{ distance }
	{
		for (int i = 0; i < sidesNumber; ++i)
		{
			add(Point{ center.x + int(distance * cos(i * 2 * pi / sidesNumber)),
				center.y - int(distance * sin(i * 2 * pi / sidesNumber)) });
		}
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Regular polygon" };

	Regular_polygon tri{ Point{150, 150}, 3, 100 };
	tri.set_color(Color::black);

	Regular_polygon sqr{ Point{300, 300}, 4, 100 };
	sqr.set_color(Color::blue);

	Regular_polygon pentagon{ Point{600, 200}, 5, 150 };
	pentagon.set_color(Color::yellow);

	win.attach(tri);
	win.attach(sqr);
	win.attach(pentagon);
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