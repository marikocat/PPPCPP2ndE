#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Striped_rectangle : public Rectangle {
	public:
		Striped_rectangle(Point c, int w, int h) : Rectangle{c, w, h} {}
		Striped_rectangle(Point tl, Point br) : Rectangle(tl, br) {}

		void draw_lines() const override;
	};

	void Striped_rectangle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			for (int i = 0; i < height(); i += 2)
				fl_line(point(0).x, point(0).y + i, point(0).x + width(), point(0).y + i);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_rect(point(0).x, point(0).y, width(), height());
		}
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point {100, 100}, 1280, 720, "Striped rectangle" };

	Striped_rectangle s_rect{ Point{100, 100}, 400, 500 };
	s_rect.set_color(Color::black);
	s_rect.set_fill_color(Color::dark_cyan);

	win.attach(s_rect);
	win.wait_for_button();
}
catch (exception& e)
{
	return 1;
}
catch (...){
	return 2;
}