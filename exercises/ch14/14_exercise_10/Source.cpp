#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Arc : public Circle {
	public:
		Arc(Point c, int r, int a1, int a2) : Circle{ c, r }, angle1{ a1 }, angle2{ a2 } {}

		void draw_lines() const override;
	private:
		int angle1;
		int angle2;
	};

	void Arc::draw_lines() const
	{
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, radius() + radius(), radius() + radius(), angle1, angle2);
			fl_color(color().as_int());
		}

		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, radius() + radius(), radius() + radius(), angle1, angle2);
		}
	}

	struct Box : Shape {
		Box(Point tl, int width, int height, int radius);

		int width() const { return w; }
		int height() const { return h; }
		int radius() const { return r; }

		void draw_lines() const override;

		void set_color(Color color);
		void set_fill_color(Color color);
		void set_style(Line_style ls);
	private:
		int w;
		int h;
		int r;
		Arc arc1;
		Arc arc2;
		Arc arc3;
		Arc arc4;
	};

	Box::Box(Point tl, int width, int height, int radius)
		: w{ width }, h{ height }, r{ radius },
		arc1{ {tl.x + radius, tl.y + radius }, radius, 90, 180},
		arc2{ {tl.x + width - radius, tl.y + radius}, radius, 0, 90 },
		arc3{ {tl.x + width - radius, tl.y + height - radius}, radius, 270, 360 },
		arc4{ {tl.x + radius, tl.y + height - radius}, radius, 180, 270 }
	{
		add(tl);
	}

	void Box::draw_lines() const
	{
		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_rectf(point(0).x + r, point(0).y, w - r * 2, r);
			fl_rectf(point(0).x + r, point(0).y + h - r, w - r * 2, r);
			fl_rectf(point(0).x, point(0).y + r, w, h - r * 2);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_color(color().as_int());
			fl_line(point(0).x + r, point(0).y, point(0).x + w - r, point(0).y); //top
			fl_line(point(0).x + r, point(0).y + h, point(0).x + w - r, point(0).y + h); //bottom
			fl_line(point(0).x, point(0).y + r, point(0).x, point(0).y + h - r); // left
			fl_line(point(0).x + w, point(0).y + r, point(0).x + w, point(0).y + h - r); // right
		}

		arc1.draw_lines();
		arc2.draw_lines();
		arc3.draw_lines();
		arc4.draw_lines();
	}

	void Box::set_color(Color color)
	{
		Shape::set_color(color);

		arc1.set_color(color);
		arc2.set_color(color);
		arc3.set_color(color);
		arc4.set_color(color);
	}

	void Box::set_fill_color(Color color)
	{
		Shape::set_fill_color(color);

		arc1.set_fill_color(color);
		arc2.set_fill_color(color);
		arc3.set_fill_color(color);
		arc4.set_fill_color(color);
	}

	void Box::set_style(Line_style ls)
	{
		Shape::set_style(ls);

		arc1.set_style(ls);
		arc2.set_style(ls);
		arc3.set_style(ls);
		arc4.set_style(ls);
	}

	class Pseudo_window : public Shape {
	public:
		Pseudo_window(Point tl, int width, int height, string label);

		void draw_lines() const override;
		int width() const { return w; }
		int height() const { return h; }
	private:
		const int box_r = 5;
		const int icon_r = 2;
		const int icon_ratio = 40;
		int w;
		int h;
		Text l;
		Box win_frame;
		Box bar;
		Circle icon;
		Box min_icon;
		Box max_icon;
		Box close_icon;
		Lines min_mark;
		Lines max_mark;
		Lines close_mark;
	};

	Pseudo_window::Pseudo_window(Point tl, int width, int height, string label)
		: w{ width }, h{ height }, l{ tl, label},
		win_frame{ tl, width, height, box_r },
		bar{ tl, width, width / icon_ratio + 2 * box_r, box_r },
		icon{{tl.x + box_r + width / icon_ratio / 2, tl.y + box_r + width / icon_ratio / 2}, width / icon_ratio / 2},
		min_icon{{tl.x + width - width / icon_ratio * 4, tl.y + box_r}, 
			width / icon_ratio , width / icon_ratio, icon_r},
		max_icon{ {tl.x + width - width / icon_ratio * 3 + box_r, tl.y + box_r}, 
			width / icon_ratio , width / icon_ratio, icon_r },
		close_icon{ {tl.x + width - width / icon_ratio * 2 + box_r * 2, tl.y + box_r}, 
			width / icon_ratio , width / icon_ratio, icon_r }
	{
		add(tl);

		l.move(box_r + width / icon_ratio * 2, bar.height() - box_r * 2);
		l.set_color(Color::white);
		l.set_font(Font::courier_bold);
		l.set_font_size(20);

		win_frame.set_color(Color::dark_cyan);
		win_frame.set_style(Line_style{ Line_style::solid, 4 });
		win_frame.set_fill_color(45);

		bar.set_color(Color::dark_cyan);
		bar.set_fill_color(Color::dark_cyan);
		bar.set_style(Line_style{ Line_style::solid, 4 });

		icon.set_color(Color::black);
		icon.set_fill_color(Color::yellow);

		min_icon.set_color(Color::white);
		max_icon.set_color(Color::white);
		close_icon.set_color(Color::white);

		int icon_width = width / icon_ratio;
		min_mark.add({ min_icon.point(0).x + icon_r * 2, min_icon.point(0).y + icon_width - 2 * icon_r },
			{ min_icon.point(0).x + icon_width - icon_r * 2, min_icon.point(0).y + icon_width - 2 * icon_r });
		min_mark.set_color(Color::white);
		min_mark.set_style(Line_style{ Line_style::solid, 2 });

		max_mark.add({ max_icon.point(0).x + icon_r * 2, max_icon.point(0).y + icon_width - 2 * icon_r },
			{ max_icon.point(0).x + icon_width - icon_r * 2, max_icon.point(0).y + icon_width - 2 * icon_r });
		max_mark.add({ max_icon.point(0).x + icon_r * 2, max_icon.point(0).y + 2 * icon_r },
			{ max_icon.point(0).x + icon_width - icon_r * 2, max_icon.point(0).y + 2 * icon_r });
		max_mark.add({ max_icon.point(0).x + icon_r * 2, max_icon.point(0).y + 2 * icon_r },
			{ max_icon.point(0).x + icon_r * 2, max_icon.point(0).y + icon_width - 2 * icon_r });
		max_mark.add({ max_icon.point(0).x + icon_width - icon_r * 2, max_icon.point(0).y + 2 * icon_r },
			{ max_icon.point(0).x + icon_width - icon_r * 2, max_icon.point(0).y + icon_width - 2 * icon_r });
		max_mark.set_color(Color::white);
		max_mark.set_style(Line_style{ Line_style::solid, 2 });

		close_mark.add({ close_icon.point(0).x + icon_r * 2, close_icon.point(0).y + icon_width - 2 * icon_r },
			{ close_icon.point(0).x + icon_width - icon_r * 2, close_icon.point(0).y + 2 * icon_r });
		close_mark.add({ close_icon.point(0).x + icon_r * 2, close_icon.point(0).y + 2 * icon_r },
			{ close_icon.point(0).x + icon_width - icon_r * 2, close_icon.point(0).y + icon_width - 2 * icon_r });
		close_mark.set_color(Color::white);
		close_mark.set_style(Line_style{ Line_style::solid, 2 });
	}

	void Pseudo_window::draw_lines() const
	{
		win_frame.draw();
		bar.draw();
		
		icon.draw();
		l.draw();

		min_icon.draw();
		max_icon.draw();
		close_icon.draw();
		min_mark.draw();
		max_mark.draw();
		close_mark.draw();
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point {100, 100}, 1280, 720, "Pseudo window" };
	Pseudo_window ps_win{ Point{100, 100}, 900, 600, "My window" };

	win.attach(ps_win);
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