#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Right_triangle : public Polygon {
	public:
		Right_triangle(Point point, int width, int height);

		int width() const { return w; }
		int height() const { return h; }
	private:
		int w;
		int h;
	};

	Right_triangle::Right_triangle(Point point, int width, int height)
		:w{width}, h{height}
	{
		add(point);
		add(Point{ point.x + width, point.y });
		add(Point{ point.x, point.y + height });
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Octagon" };

	Vector_ref<Right_triangle> triVector;
	triVector.push_back(new Right_triangle{ Point {250, 250}, -150, -150 });
	triVector.push_back(new Right_triangle{ Point {250, 450}, -150, 150 });
	triVector.push_back(new Right_triangle{ Point {450, 250}, 150, -150 });
	triVector.push_back(new Right_triangle{ Point {450, 450}, 150, 150 });
	triVector.push_back(new Right_triangle{ Point {250, 100}, 200, 500 });
	triVector.push_back(new Right_triangle{ Point {450, 600}, -200, -500 });
	triVector.push_back(new Right_triangle{ Point {100, 250}, 500, 200 });
	triVector.push_back(new Right_triangle{ Point {600, 450}, -500, -200 });

	for (int i = 0; i < triVector.size(); ++i)
	{
		triVector[i].set_color(Color(i));
		win.attach(triVector[i]);
	}
	win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}