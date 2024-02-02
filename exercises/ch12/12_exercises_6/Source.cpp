//#include<FL/Fl.h>
//#include<FL/Fl_Box.h>
//#include<FL/Fl_Window.h>
//
//int main()
//{
//	Fl_Window window(200, 200, "Window title");
//	Fl_Box box(0, 0, 200, 200, "Hey, I mean, Hello, World!");
//	window.show();
//	return Fl::run();
//}

#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
try
{
	Simple_window win{ Point{0, 0}, 1920, 1000, "My window" };
	Graph_lib::Rectangle rect{ Point{100, 100}, 2000, 500 };
	rect.fill_color();
	rect.set_fill_color(Color::yellow);
	win.attach(rect);
	win.wait_for_button();
}
catch (exception& e) {

}
catch (...) {

}