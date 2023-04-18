#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

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

	class Smiley : public Circle {
	public:
		Smiley(Point c, int r) : Circle{c, r},
			left_eye{ {c.x - int(r / 2 * cos(45 * pi / 180)), c.y - int(r / 2 * sin(45 * pi / 180))}, '*'},
			right_eye{ {c.x + int(r / 2 * cos(45 * pi / 180)), c.y - int(r / 2 * sin(45 * pi / 180))}, '*' },
			smile{ {c.x, c.y}, r / 2, 200, 340 } {}

		void draw_lines() const override;

		void set_color(Color color);
	private:
		Mark left_eye;
		Mark right_eye;
		Arc smile;
	};

	void Smiley::draw_lines() const
	{
		Circle::draw_lines();

		left_eye.draw_lines();
		right_eye.draw_lines();
		smile.draw_lines();
	}

	void Smiley::set_color(Color color)
	{
		Circle::set_color(color);

		left_eye.set_color(color);
		right_eye.set_color(color);
		smile.set_color(color);
	}

	class Smiley_with_hat : public Smiley {
	public:
		Smiley_with_hat(Point c, int r);

		void draw_lines() const override;

		void set_color(Color color);
	private:
		Open_polyline hat;
	};

	Smiley_with_hat::Smiley_with_hat(Point c, int r) :
		Smiley{ c, r }
	{
		hat.add({ int(c.x - r * cos(45 * pi / 180)), int(c.y - r * sin(45 * pi / 180)) });
		hat.add({ c.x, c.y - r * 2 });
		hat.add({ int(c.x + r * cos(45 * pi / 180)), int(c.y - r * sin(45 * pi / 180)) });
	}

	void Smiley_with_hat::draw_lines() const
	{
		Smiley::draw_lines();

		hat.draw_lines();
	}

	void Smiley_with_hat::set_color(Color color)
	{
		Smiley::set_color(color);

		hat.set_color(color);
	}

	class Frowny : public Circle {
	public:
		Frowny(Point c, int r) : Circle{ c, r },
			left_eye{ {c.x - int(r / 2 * cos(45 * pi / 180)), c.y - int(r / 2 * sin(45 * pi / 180))}, 'o' },
			right_eye{ {c.x + int(r / 2 * cos(45 * pi / 180)), c.y - int(r / 2 * sin(45 * pi / 180))}, 'o' },
			smile{ {c.x, c.y + r / 2}, r / 2, 20, 160 } {}

		void draw_lines() const override;

		void set_color(Color color);
	private:
		Mark left_eye;
		Mark right_eye;
		Arc smile;
	};

	void Frowny::draw_lines() const
	{
		Circle::draw_lines();

		left_eye.draw_lines();
		right_eye.draw_lines();
		smile.draw_lines();
	}

	void Frowny::set_color(Color color)
	{
		Circle::set_color(color);

		left_eye.set_color(color);
		right_eye.set_color(color);
		smile.set_color(color);
	}

	class Frowny_with_hat : public Frowny {
	public:
		Frowny_with_hat(Point c, int r);

		void draw_lines() const override;

		void set_color(Color color);
	private:
		Open_polyline hat;
	};

	Frowny_with_hat::Frowny_with_hat(Point c, int r) :
		Frowny{ c, r }
	{
		hat.add({ int(c.x + r * cos(45 * pi / 180)), int(c.y - r * sin(45 * pi / 180)) });
		hat.add({ hat.point(0).x, hat.point(0).y - r / 2 });
		hat.add({ int(c.x - r * cos(45 * pi / 180)), hat.point(1).y });
		hat.add({ hat.point(2).x, int(c.y - r * sin(45 * pi / 180)) });
	}

	void Frowny_with_hat::draw_lines() const
	{
		Frowny::draw_lines();

		hat.draw_lines();
	}

	void Frowny_with_hat::set_color(Color color)
	{
		Frowny::set_color(color);

		hat.set_color(color);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Smiley and frowny" };

	Smiley_with_hat sm_face{ Point{300, 450}, 200 };
	sm_face.set_color(Color::black);
	sm_face.set_fill_color(Color::yellow);

	Frowny_with_hat fr_face{ Point{900, 450}, 200 };
	fr_face.set_color(Color::black);
	fr_face.set_fill_color(Color::yellow);

	win.attach(sm_face);
	win.attach(fr_face);
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