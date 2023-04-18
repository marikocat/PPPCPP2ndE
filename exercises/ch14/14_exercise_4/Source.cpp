#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Immobile_circle : public Circle {
	public:
		Immobile_circle(Point c, int r) : Circle{ c, r } {}

		void move(int dx, int dy) override {}
	};
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Immobile_circle" };

	Immobile_circle i_circle{ Point{250, 250}, 100 };
	i_circle.set_color(Color::black);

	win.attach(i_circle);
	win.wait_for_button();

	i_circle.move(100, 100);
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