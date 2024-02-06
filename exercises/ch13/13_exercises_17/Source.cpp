#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	class Regular_hexagon : public Graph_lib::Polygon {
	public:
		Regular_hexagon(Point center, int distance);

		Point center() const { return c; }
		int radius() const { return d; }
	private:
		Point c;
		int d;
	};

	Regular_hexagon::Regular_hexagon(Point center, int distance)
		:c{ center }, d{ distance }
	{
		add(Point{ center.x + distance, center.y });
		add(Point{ center.x + int(distance * sin(30 * pi / 180)), center.y + int(distance * cos(30 * pi / 180)) });
		add(Point{ center.x - int(distance * sin(30 * pi / 180)), point(1).y });
		add(Point{ center.x - distance, point(0).y });
		add(Point{ point(2).x, center.y - int(distance * cos(30 * pi / 180)) });
		add(Point{ point(1).x, point(4).y });
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1250, 800, "Tiled with hexagons" };

	const int radius = 100;

	Vector_ref<Regular_hexagon> hexVector;
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 4; ++j)
		{
			hexVector.push_back(new Regular_hexagon{ Point{int(radius * (i % 2 == 0 ? 1 : 2.5)) + j * radius * 3,
				int(radius * cos(30 * pi / 180)) + i * int(radius * cos(30 * pi / 180))}, radius });
			hexVector[hexVector.size() - 1].set_color(Color::black);
			hexVector[hexVector.size() - 1].set_fill_color(Color(i));
			win.attach(hexVector[hexVector.size() - 1]);
		}


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