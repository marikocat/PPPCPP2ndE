#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	Simple_window s_win{ Point{100, 100}, 1600, 900, "My window" };
	Graph_lib::Rectangle rect{ Point{500, 300}, 600, 500 };
	rect.set_color(Color::black);
	s_win.attach(rect);

	Graph_lib::Polygon roof;
	roof.add(Point{ 500, 300 });
	roof.add(Point{ 1100, 300 });
	roof.add(Point{ 800, 150 });
	roof.set_color(Color::black);
	s_win.attach(roof);

	Graph_lib::Rectangle window{ Point{550, 400}, 200, 200 };
	window.set_color(Color::black);
	window.fill_color();
	window.set_fill_color(Color::white);
	s_win.attach(window);

	Graph_lib::Rectangle door{ Point{850, 400}, 200, 400 };
	door.set_color(Color::black);
	s_win.attach(door);

	Graph_lib::Rectangle glass1{ Point{570, 420}, 70, 70 };
	glass1.set_color(Color::black);
	glass1.fill_color();
	glass1.set_fill_color(Color::cyan);
	s_win.attach(glass1);
	Graph_lib::Rectangle glass2{ Point{570, 510}, 70, 70 };
	glass2.set_color(Color::black);
	glass2.fill_color();
	glass2.set_fill_color(Color::cyan);
	s_win.attach(glass2);
	Graph_lib::Rectangle glass3{ Point{660, 420}, 70, 70 };
	glass3.set_color(Color::black);
	glass3.fill_color();
	glass3.set_fill_color(Color::cyan);
	s_win.attach(glass3);
	Graph_lib::Rectangle glass4{ Point{660, 510}, 70, 70 };
	glass4.set_color(Color::black);
	glass4.fill_color();
	glass4.set_fill_color(Color::cyan);
	s_win.attach(glass4);

	s_win.wait_for_button();
}