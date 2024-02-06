#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Circle" };

	Circle circle{ Point{250, 250}, 150 };
	circle.set_color(Color::black);

	Mark m{ Point{circle.center().x + int(circle.radius() * cos(0 * pi / 180)),
		circle.center().y - int(circle.radius() * sin(0 * pi / 180))}, 'x' };

	win.attach(circle);
	win.attach(m);
	win.wait_for_button();

	for (int i = 1; i < 24; ++i)
	{
		m.move(circle.center().x + int(circle.radius() * cos(15 * i * pi / 180)) - m.point(0).x,
			circle.center().y - int(circle.radius() * sin(15 * i * pi / 180)) - m.point(0).y);
		win.wait_for_button();
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