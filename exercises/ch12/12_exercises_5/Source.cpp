#include "Simple_window.h"
#include "Graph.h"

#include <iostream>

int main()
{
	using namespace Graph_lib;

	const int inch = 96; // pixels in 1 inch
	const int rect_width = x_max() * 2 / 3;
	const int rect_height = y_max() * 3 / 4;

	const Point tl{ 50, 50 };
	Simple_window s_win{ tl, rect_width + 100, rect_height + 100, "Canvas #1"};

	Graph_lib::Rectangle rect{ Point{ 50 , 50 }, rect_width, rect_height };
	rect.set_fill_color(Color::white);
	rect.set_color(Color::black);
	rect.set_style(Line_style(Line_style::solid, 8));
	Graph_lib::Rectangle frame{ Point{ 50 - inch / 8, 50 - inch / 8 }, Point{50 + rect_width + inch / 8, 50 + rect_height + inch / 8} };
	frame.set_color(Color::red);
	frame.set_style(Line_style(Line_style::dash, inch / 4));
	s_win.attach(rect);
	s_win.attach(frame);
	
	s_win.wait_for_button();
}