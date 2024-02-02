#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4; // arctg(1) = Pi/4

int sgn(double d);
void set_points(vector<Point>&, Point, double, double, double, double);

int main()
try {
	using namespace Graph_lib;

	const Point tl{ x_max() / 4, y_max() / 4 };
	Simple_window s_win{ tl, x_max() / 4, x_max() / 4, "My window" };

	vector<Point> points;
	const Point origin{ s_win.x_max() / 2, s_win.y_max() / 2 };
	const double a = 1;
	const double b = 1;
	const double m = 0.5;
	const double n = 0.5;
	set_points(points, origin, a, b, m, n);

	Open_polyline superellipse;
	int i = 0;
	for (Point p : points) {
		superellipse.add(p);

		cout << ++i << " " << p.x << " " << p.y << "\n";
	}
	superellipse.set_color(Color::black);
	s_win.attach(superellipse);

	const int N = 25;
	const int increment = 1 + points.size() / N;
	cout << "points size: " << points.size() << "\n";
	cout << "increment: " << increment << "\n";

	vector<Graph_lib::Color> colors = { Color::green, Color::yellow, Color::red, Color::blue };
	vector<Line*> lines;
	for (int i = 0; i < N; ++i) {
		Line* line = new Line{ points[i * increment % points.size()], points[0] };
		line->set_color(colors[i % colors.size()]);
		lines.push_back(line);
	}
	for (Line* line : lines)
		s_win.attach(*line);

	s_win.wait_for_button();

	for (Line* line : lines)
		delete line;
	lines.clear();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
	return 1;
}
catch (...) {
	cerr << "Unexpected error.\n";
	return 2;
}

void set_points(vector<Point>& points, Point origin, double a, double b, double m, double n)
{
	Point point;
	const double increment = 0.01;
	for (double d = -1; d <= 1; d += increment)
	{
		double t = d * pi;
		double x = pow((abs(cos(t))), 2 / m) * a * sgn(cos(t));
		double y = pow((abs(sin(t))), 2 / n) * b * sgn(sin(t));
		point = Point{ origin.x + int(x * origin.x), origin.y + int(y * origin.y) };

		bool duplicate = false;
		for (Point temp : points)
			if (point == temp)
				duplicate = true;
		if (!duplicate)
			points.push_back(point);
	}
}

int sgn(double d)
{
	if (d < 0) return -1;
	if (d == 0) return 0;
	return 1;
}