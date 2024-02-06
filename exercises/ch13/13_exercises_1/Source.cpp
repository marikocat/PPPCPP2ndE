#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	struct Arc : Shape {
		Arc(Point p, int rr, int b, int e);

		void draw_lines() const;

		Point center() const;
		int radius() const { return r; }
		void set_radius(int rr)
		{
			set_point(0, Point{ center().x - rr, center().y - rr });
			r = rr;
		}
	private:
		int r;
		int ba;
		int ea;
	};

	Arc::Arc(Point p, int rr, int b, int e) :r{ rr }, ba{ b }, ea{ e }
	{
		add(Point{ p.x - r, p.y - r });
	}

	Point Arc::center() const
	{
		return { point(0).x + r, point(0).y + r };
	}

	void Arc::draw_lines() const
	{
		if (color().visibility())
			fl_arc(point(0).x, point(0).y, r + r, r + r, ba, ea);
	}

	struct ArcEll : Shape {
		ArcEll(Point pp, int ww, int hh, int ba, int ea);

		void draw_lines() const;

		Point center() const;
		Point focus1() const;
		Point focus2() const;

		void set_major(int ww)
		{
			set_point(0, Point{ center().x - ww, center().y - h });
			w = ww;
		}
		int major() const { return w; }

		void set_minor(int hh)
		{
			set_point(0, Point{ center().x - w, center().y - hh });
			h = hh;
		}
		int minor() const { return h; }
	private:
		int w;
		int h;
		int b;
		int e;
	};

	ArcEll::ArcEll(Point pp, int ww, int hh, int ba, int ea)
		:w{ ww }, h{ hh }, b{ ba }, e{ ea }
	{
		add(Point{pp.x - ww, pp.y - hh});
	}

	Point ArcEll::center() const
	{
		return { point(0).x + w, point(0).y + h };
	}

	Point ArcEll::focus1() const
	{
		if (h <= w) // foci are on the x axis:
			return { center().x + int(sqrt(double(w * w - h * h))), center().y };
		else
			return { center().x, center().y + int(sqrt(double(h * h - w * w))) };
	}
	Point ArcEll::focus2() const
	{
		if (h <= w) // foci are on the x axis:
			return { center().x - int(sqrt(double(w * w - h * h))), center().y };
		else
			return { center().x, center().y - int(sqrt(double(h * h - w * w))) };
	}
	

	void ArcEll::draw_lines() const
	{
		if (color().visibility()) {
			fl_color(color().as_int());
			fl_arc(point(0).x, point(0).y, w + w, h + h, b, e);
		}
	}
}

int main()
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 400, "Arc" };

	Graph_lib::Arc arc{ Point{200, 200}, 100, 0, 180 };
	arc.set_color(Color::black);

	win.attach(arc);

	win.wait_for_button();

	arc.set_radius(150);

	win.wait_for_button();

	ArcEll arcEllipse{ Point{200, 200}, 150, 100, 0, 180 };
	arc.set_color(Color::black);

	win.attach(arcEllipse);

	win.wait_for_button();
}