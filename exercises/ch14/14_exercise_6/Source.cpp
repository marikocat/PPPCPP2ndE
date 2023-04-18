#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Striped_circle : public Circle {
	public:
		Striped_circle(Point c, int r) : Circle{c, r} {}

		void draw_lines() const override;
	};

	void Striped_circle::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			//fl_pie(point(0).x, point(0).y, r + r - 1, r + r - 1, 0, 360);
			for (int i = 0; i < radius() * 2; i += 4)
			{
				int dy = point(0).y + i - center().y;
				int dx = int(sqrt(radius() * radius() - dy * dy));
				fl_line(center().x - dx, 
					center().y + dy, 
					center().x + dx, 
					center().y + dy);
			}
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, radius() + radius(), radius() + radius(), 0, 360);
		}
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Striped circle" };

	Striped_circle s_circle{ Point{600, 350}, 200 };
	s_circle.set_color(Color::black);
	s_circle.set_fill_color(Color::dark_blue);

	win.attach(s_circle);
	win.wait_for_button();
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}