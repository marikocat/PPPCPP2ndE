#include "Simple_window.h"
#include "Graph.h"
#include <cmath>

double to_radians(int degrees) { return degrees * atan(1) * 4 / 180; }

using namespace Graph_lib;

int main()
{
	Simple_window s_win{ Point{200, 200}, x_max() / 2, y_max() / 2, "Mywindow" };

	const int side_length = 200;

	Graph_lib::Polygon hexagon;
	hexagon.add(Point{ s_win.x_max() / 2 - 100, s_win.y_max() - 100 });
	hexagon.add(Point{ hexagon.point(0).x + 200, hexagon.point(0).y });
	hexagon.add(Point{ hexagon.point(1).x + int(cos(to_radians(60)) * side_length), 
		hexagon.point(1).y - int(cos(to_radians(30)) * side_length) });
	hexagon.add(Point{ hexagon.point(1).x,
		hexagon.point(1).y - int(cos(to_radians(30)) * side_length) * 2 });
	hexagon.add(Point{ hexagon.point(0).x,
		hexagon.point(3).y });
	hexagon.add(Point{ hexagon.point(4).x - int(cos(to_radians(60)) * side_length),
		hexagon.point(2).y });

	hexagon.set_color(Color::black);
	s_win.attach(hexagon);

	Graph_lib::Polygon pentagon;
	pentagon.add(Point{ hexagon.point(4).x + side_length / 2,
		hexagon.point(4).y });
	const double pentagon_side = (100 * sin(to_radians(120)) / sin(to_radians(24)));
	pentagon.add(Point{ pentagon.point(0).x + int(cos(to_radians(36)) * pentagon_side),
		pentagon.point(0).y + int(cos(to_radians(54)) * pentagon_side) });
	pentagon.add(Point{ pentagon.point(1).x - int(cos(to_radians(72)) * pentagon_side),
		pentagon.point(1).y + int(cos(to_radians(18)) * pentagon_side) });
	pentagon.add(Point{ pentagon.point(2).x - int(pentagon_side),
		pentagon.point(2).y });
	pentagon.add(Point{ pentagon.point(0).x - int(cos(to_radians(36)) * pentagon_side),
		pentagon.point(0).y + int(cos(to_radians(54)) * pentagon_side) });

	pentagon.set_color(Color::black);
	s_win.attach(pentagon);

	Graph_lib::Polygon square;
	square.add(Point{ pentagon.point(3).x, pentagon.point(3).y });
	square.add(Point{ pentagon.point(2).x, pentagon.point(2).y });
	square.add(Point{ pentagon.point(2).x, pentagon.point(2).y - int(pentagon_side) });
	square.add(Point{ pentagon.point(3).x, pentagon.point(3).y - int(pentagon_side) });

	square.set_color(Color::black);
	s_win.attach(square);

	Graph_lib::Polygon triangle;
	triangle.add(Point{ square.point(0).x, square.point(0).y });
	triangle.add(Point{ square.point(1).x, triangle.point(0).y - int(tan(to_radians(15)) * pentagon_side)});
	triangle.add(Point{ triangle.point(0).x + int(tan(to_radians(15)) * pentagon_side), square.point(2).y });

	triangle.set_color(Color::black);
	s_win.attach(triangle);

	s_win.wait_for_button();
}