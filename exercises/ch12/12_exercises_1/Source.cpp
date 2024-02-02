#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
try
{
	Simple_window win{ Point{200, 200}, 1200, 720, "Canvas #1" };
	Graph_lib::Rectangle rect{ Point{100, 100}, 300, 150 };
	rect.set_color(Color::blue);
	win.attach(rect);

	Graph_lib::Polygon poly;
	poly.add(Point{ 100, 350 });
	poly.add(Point{ 400, 350 });
	poly.add(Point{ 400, 500 });
	poly.add(Point{ 100, 500 });
	poly.set_color(Color::red);
	win.attach(poly);

	win.wait_for_button();
}
catch (exception& e) {
	return 1;
}
catch (...) {
	return 2;
}