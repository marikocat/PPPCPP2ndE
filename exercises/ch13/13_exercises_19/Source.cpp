#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	class Star : public Polygon {
	public:
		Star(Point center, int numberOfPoints, int externalRadius, int internalRadius);

		Point center() const { return c; }
		int pointsNum() const { return n; }
		int externalRadius() const { return er; }
		int internalRadius() const { return ir; }
	private:
		Point c;
		int n;
		int er;
		int ir;
	};

	Star::Star(Point center, int numberOfPoints, int externalRadius, int internalRadius)
		:c{ center }, n{ numberOfPoints }, er{ externalRadius }, ir{ internalRadius }
	{
		for (int i = 0; i < numberOfPoints; ++i)
		{
			add(Point{ center.x + int(externalRadius * cos(i * 2 * pi / numberOfPoints)),
				center.y - int(externalRadius * sin(i * 2 * pi / numberOfPoints)) });
			add(Point{ center.x + int(internalRadius * cos((i + 0.5) * 2 * pi / numberOfPoints)),
				center.y - int(internalRadius * sin((i + 0.5) * 2 * pi / numberOfPoints)) });
		}
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Stars" };

	Star star1{ Point{250, 250}, 5, 150, 100 };
	star1.set_color(Color::black);
	star1.set_fill_color(Color::white);

	Star star2{ Point{700, 350}, 6, 200, 120 };
	star2.set_color(Color::dark_cyan);
	star2.set_fill_color(Color::cyan);

	Star star3{ Point{1050, 500}, 4, 200, 80 };
	star3.set_color(Color::dark_magenta);
	star3.set_fill_color(Color::magenta);

	win.attach(star1);
	win.attach(star2);
	win.attach(star3);
	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}