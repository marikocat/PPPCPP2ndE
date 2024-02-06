#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	struct Box : Shape {
		Box(Point tl, int ww, int hh, int rr, string ss);

		void set_font(Font f);
		void set_font_size(int s);

		void draw_lines() const;

		Point north_center() const
		{
			return { point(0).x + w / 2, point(0).y };
		}

		int radius() const
		{
			return r;
		}
		int width() const
		{
			return w;
		}
		int height() const
		{
			return h;
		}
	private:
		int w;
		int h;
		int r;
		Text text;
	};

	Box::Box(Point tl, int ww, int hh, int rr, string ss)
		: w{ ww }, h{ hh }, r{ rr },
		text{ Point{tl.x + rr, tl.y + hh - rr }, ss }
	{
		add(tl);
	}

	void Box::set_font(Font f)
	{
		text.set_font(f);
	}

	void Box::set_font_size(int s)
	{
		text.set_font_size(s);
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

		if (fill_color().visibility()) {	// fill
			fl_color(fill_color().as_int());
			fl_pie(point(0).x, point(0).y, r + r, r + r, 90, 180);
			fl_pie(point(0).x + w - r - r, point(0).y, r + r, r + r, 0, 90);
			fl_pie(point(0).x, point(0).y + h - r - r, r + r, r + r, 180, 270);
			fl_pie(point(0).x + w - r - r, point(0).y + h - r - r, r + r, r + r, 270, 360);
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility()) {	// edge on top of fill
			fl_arc(point(0).x, point(0).y, r + r, r + r, 90, 180);
			fl_arc(point(0).x + w - r - r, point(0).y, r + r, r + r, 0, 90);
			fl_arc(point(0).x, point(0).y + h - r - r, r + r, r + r, 180, 270);
			fl_arc(point(0).x + w - r - r, point(0).y + h - r - r, r + r, r + r, 270, 360);
		}

		text.draw_lines();
	}

	struct Arrow : Shape {
		Arrow(Point start, Point end, double head_angle, int head_size);

		void set_color(Graph_lib::Color);
		void set_style(Graph_lib::Line_style);
		void set_fill_color(Graph_lib::Color);

		void draw_lines() const;
	private:
		Graph_lib::Polygon head;
	};

	Arrow::Arrow(Point start, Point end, double head_angle, int head_size)
	{
		add(start);
		add(end);

		double line_angle = atan2(end.y - start.y, end.x - start.x);

		head.add(end);
		head.add({ int(point(1).x - head_size * cos(line_angle + head_angle)),
			int(point(1).y - head_size * sin(line_angle + head_angle)) });
		head.add({ int(point(1).x - head_size * cos(line_angle - head_angle)),
			int(point(1).y - head_size * sin(line_angle - head_angle)) });
	}

	void Arrow::set_color(Graph_lib::Color c)
	{
		Shape::set_color(c);
		head.set_color(c);
	}
	void Arrow::set_style(Graph_lib::Line_style ls)
	{
		Shape::set_style(ls);
		head.set_style(ls);
	}
	void Arrow::set_fill_color(Graph_lib::Color c)
	{
		head.set_fill_color(c);
	}

	void Arrow::draw_lines() const
	{
		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

		head.draw_lines();
	}
}

int main()
{
	Simple_window win{ Point{100, 100}, 1720, 880, "Diagram" };

	Graph_lib::Box box1{ Point{300, 50}, 150, 50, 10, "Window" };
	box1.set_color(Color::black);
	box1.set_fill_color(Color::green);
	box1.set_font_size(24);

	Graph_lib::Box box2{ Point{700, 50}, 150, 50, 10, "Line_style" };
	box2.set_color(Color::black);
	box2.set_fill_color(Color::green);
	box2.set_font_size(24);

	Graph_lib::Box box3{ Point{1100, 50}, 150, 50, 10, "Color" };
	box3.set_color(Color::black);
	box3.set_fill_color(Color::green);
	box3.set_font_size(24);

	Graph_lib::Box box4{ Point{200, 250}, 250, 50, 10, "Simple_window" };
	box4.set_color(Color::black);
	box4.set_fill_color(Color::green);
	box4.set_font_size(24);

	Graph_lib::Box box5{ Point{750, 250}, 150, 50, 10, "Shape" };
	box5.set_color(Color::black);
	box5.set_fill_color(Color::green);
	box5.set_font_size(24);

	Graph_lib::Box box6{ Point{1150, 250}, 150, 50, 10, "Point" };
	box6.set_color(Color::black);
	box6.set_fill_color(Color::green);
	box6.set_font_size(24);

	Graph_lib::Box box7{ Point{150, 500}, 150, 50, 10, "Line" };
	box7.set_color(Color::black);
	box7.set_fill_color(Color::green);
	box7.set_font_size(24);

	Graph_lib::Box box8{ Point{350, 500}, 150, 50, 10, "Lines" };
	box8.set_color(Color::black);
	box8.set_fill_color(Color::green);
	box8.set_font_size(24);

	Graph_lib::Box box9{ Point{550, 500}, 150, 50, 10, "Polygon" };
	box9.set_color(Color::black);
	box9.set_fill_color(Color::green);
	box9.set_font_size(24);

	Graph_lib::Box box10{ Point{750, 500}, 150, 50, 10, "Axis" };
	box10.set_color(Color::black);
	box10.set_fill_color(Color::green);
	box10.set_font_size(24);

	Graph_lib::Box box11{ Point{950, 500}, 150, 50, 10, "Rectangle" };
	box11.set_color(Color::black);
	box11.set_fill_color(Color::green);
	box11.set_font_size(24);

	Graph_lib::Box box12{ Point{1150, 500}, 150, 50, 10, "Text" };
	box12.set_color(Color::black);
	box12.set_fill_color(Color::green);
	box12.set_font_size(24);

	Graph_lib::Box box13{ Point{1350, 500}, 150, 50, 10, "Image" };
	box13.set_color(Color::black);
	box13.set_fill_color(Color::green);
	box13.set_font_size(24);

	win.attach(box1);
	win.attach(box2);
	win.attach(box3);
	win.attach(box4);
	win.attach(box5);
	win.attach(box6);
	win.attach(box7);
	win.attach(box8);
	win.attach(box9);
	win.attach(box10);
	win.attach(box11);
	win.attach(box12);
	win.attach(box13);

	Graph_lib::Arrow arr1{ box7.north_center(), 
		{box5.point(0).x + box5.radius(), box5.point(0).y + box5.height()}, 15 * pi / 180, 20};
	Graph_lib::Arrow arr2{ box8.north_center(), 
		{box5.point(0).x + box5.width() / box5.radius() * 2, box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	Graph_lib::Arrow arr3{ box9.north_center(),
		{box5.point(0).x + box5.width() / box5.radius() * 3, box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	Graph_lib::Arrow arr4{ box10.north_center(),
		{box5.point(0).x + box5.width() / 2, box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	Graph_lib::Arrow arr5{ box11.north_center(),
		{box5.point(0).x + box5.width() - box5.width() / box5.radius() * 3, box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	Graph_lib::Arrow arr6{ box12.north_center(),
		{box5.point(0).x + box5.width() - box5.width() / box5.radius() * 2, box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	Graph_lib::Arrow arr7{ box13.north_center(),
		{box5.point(0).x + box5.width() - box5.radius(), box5.point(0).y + box5.height()}, 15 * pi / 180, 20 };
	arr1.set_color(Color::black);
	arr2.set_color(Color::black);
	arr3.set_color(Color::black);
	arr4.set_color(Color::black);
	arr5.set_color(Color::black);
	arr6.set_color(Color::black);
	arr7.set_color(Color::black);
	arr1.set_fill_color(Color::black);
	arr2.set_fill_color(Color::black);
	arr3.set_fill_color(Color::black);
	arr4.set_fill_color(Color::black);
	arr5.set_fill_color(Color::black);
	arr6.set_fill_color(Color::black);
	arr7.set_fill_color(Color::black);

	win.attach(arr1);
	win.attach(arr2);
	win.attach(arr3);
	win.attach(arr4);
	win.attach(arr5);
	win.attach(arr6);
	win.attach(arr7);

	win.wait_for_button();
}