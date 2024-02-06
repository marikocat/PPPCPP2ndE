#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	struct Box : Shape {
		Box(Point tl, int ww, int hh, int rr);

		void draw_lines() const;
	private:
		int w;
		int h;
		int r;
	};

	Box::Box(Point tl, int ww, int hh, int rr)
		: w{ww}, h{hh}, r{rr}
	{
		add(tl);
	}

	void Box::draw_lines() const
	{
		fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y); //top
		fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h); //bottom
		fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r); // left
		fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r); // right

		fl_arc(point(0).x, point(0).y, r+r, r+r, 90, 180);
		fl_arc(point(0).x + w - r - r, point(0).y, r+r, r+r, 0, 90);
		fl_arc(point(0).x, point(0).y + h - r - r, r+r, r+r, 180, 270);
		fl_arc(point(0).x + w - r - r, point(0).y + h - r - r, r+r, r+r, 270, 360);
	}
}

int main()
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 400, "Box" };

	Box box{ Point{50, 50}, 400, 200, 20 };
	box.set_color(Color::black);

	win.attach(box);

	win.wait_for_button();
}