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
		:w{ width }, h{ height }
	{
		add(point);
		add(Point{ point.x + width, point.y });
		add(Point{ point.x, point.y + height });
	}
}

int main()
try {
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1200, 700, "Tiled with triangles" };

	Vector_ref<Right_triangle> triVector;
	for (int i = 0; i < 7; ++i)
		for (int j = 0; j < 24; ++j)
		{
			triVector.push_back(new Right_triangle{ Point{j * 50 + (j % 2 == 0 ? 0: 50), i * 100},
				100 * (j % 2 == 0 ? 1 : -1), 100 * (j % 2 == 0 ? 1 : -1) });
			triVector[triVector.size() - 1].set_color(Color::black);
			win.attach(triVector[triVector.size() - 1]);
		}

	win.wait_for_button();
}
catch (exception& e) {
	cerr << "Error: " << e.what() << ".\n";
}
catch (...) {
	cerr << "Unexpected error.\n";
}