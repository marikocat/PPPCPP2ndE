#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
try
{
	Simple_window s_win{ Point{100, 100}, 800, 600, "My window" };
	Graph_lib::Circle circle1{ Point{200, 200}, 90 };
	circle1.set_style(Line_style(Line_style::solid, 8));
	circle1.set_color(Color::blue);
	s_win.attach(circle1);

	Graph_lib::Circle circle2{ Point{400, 200}, 90 };
	circle2.set_style(Line_style(Line_style::solid, 8));
	circle2.set_color(Color::black);
	s_win.attach(circle2);

	Graph_lib::Circle circle3{ Point{600, 200}, 90 };
	circle3.set_style(Line_style(Line_style::solid, 8));
	circle3.set_color(Color::red);
	s_win.attach(circle3);

	Graph_lib::Circle circle4{ Point{300, 300}, 90 };
	circle4.set_style(Line_style(Line_style::solid, 8));
	circle4.set_color(Color::yellow);
	s_win.attach(circle4);

	Graph_lib::Circle circle5{ Point{500, 300}, 90 };
	circle5.set_style(Line_style(Line_style::solid, 8));
	circle5.set_color(Color::green);
	s_win.attach(circle5);

	s_win.wait_for_button();
}
catch (exception& e) {
	return 1;
}
catch (...) {
	return 2;
}