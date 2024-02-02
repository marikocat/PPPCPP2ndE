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

	Graph_lib::Rectangle rect2{ Point{100, 600}, 100, 30 };
	win.attach(rect2);
	Text t{ Point{130, 620}, "Howdy!" };
	t.set_color(Color::black);
	win.attach(t);
	win.set_label("Canvas #2");
	win.wait_for_button();

	Graph_lib::Open_polyline opline;
	opline.add(Point{ 600, 250 });
	opline.add(Point{ 625, 100 });
	opline.add(Point{ 650, 250 });
	opline.add(Point{ 675, 100 });
	opline.add(Point{ 700, 250 });
	opline.set_color(Color::cyan);
	opline.set_style(Line_style(Line_style::solid, 6));
	win.attach(opline);
	Graph_lib::Open_polyline opline2;
	opline2.add(Point{ 750, 100 });
	opline2.add(Point{ 750, 250 });
	opline2.set_color(Color::dark_cyan);
	opline2.set_style(Line_style(Line_style::solid, 6));
	win.attach(opline2);
	win.set_label("Canvas #3");
	win.wait_for_button();
}
catch (exception& e) {
	return 1;
}
catch (...) {
	return 2;
}