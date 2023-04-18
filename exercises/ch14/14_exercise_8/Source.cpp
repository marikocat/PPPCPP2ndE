#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	class Octagon : public Polygon {
	public:
		Octagon(Point center, int radius);

		Point center() const { return { point(0).x - r, point(0).y }; }
		int radius() const { return r; }
	private:
		int r;
	};

	Octagon::Octagon(Point center, int radius)
		: r{ radius }
	{
		const int vert_num = 8;
		for (int i = 0; i < vert_num; ++i)
			add(Point{ int(center.x + radius * cos(i * 2 * pi / vert_num)),
				int(center.y - radius * sin(i * 2 * pi / vert_num)) });
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Regular octagon" };

	Octagon octagon{ Point{350, 250}, 250 };
	octagon.set_color(Color::black);
	octagon.set_fill_color(Color::blue);
	octagon.set_style(Line_style(Line_style::dash, 2));
	octagon.move(350, 150);
	cout << "center (" << octagon.center().x << ", " << octagon.center().y << ");\n";
	cout << "radius " << octagon.radius() << ";\n";

	win.attach(octagon);
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