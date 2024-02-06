#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	struct Arrow : Shape {
		Arrow(Point start, Point end, double head_angle, int head_size)
			: ha{head_angle}, hs{head_size}
		{
			add(start);
			add(end);
		}

		void draw_lines() const;
	private:
		double ha;
		int hs;
	};

	void Arrow::draw_lines() const
	{
		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

		double line_angle = atan2(point(1).y - point(0).y, point(1).x - point(0).x);

		fl_line(point(1).x, 
			point(1).y, 
			int(point(1).x - hs * cos(line_angle + ha)), 
			int(point(1).y - hs * sin(line_angle + ha)));
		fl_line(point(1).x, 
			point(1).y, 
			int(point(1).x - hs * cos(line_angle - ha)),
			int(point(1).y - hs * sin(line_angle - ha)));
	}
}

int main()
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 400, "Arrow" };

	Arrow arrow{ Point{300, 250}, Point{400, 150}, 15 * pi / 180, 50 };
	arrow.set_color(Color::black);

	win.attach(arrow);

	win.wait_for_button();
}