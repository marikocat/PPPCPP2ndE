#include "Gui.h"

using namespace Graph_lib;

const double pi = atan(1) * 4;

class Regular_polygon : public Shape {
public:
	Regular_polygon(Point, int, int);

	void draw_lines() const override;

	Point center() const { return c; }
private:
	Point c;
	int r;
	int n;
};

Regular_polygon::Regular_polygon(Point center, int radius, int sides_num)
	: c{center}, r{radius}, n{sides_num}
{
	for (int i = 0; i < sides_num; ++i)
	{
		add(Point{ center.x + int(radius * cos(i * 360 / sides_num * pi / 180)),
			center.y - int(radius * sin(i * 360 / sides_num * pi / 180)) });
	}
}

void Regular_polygon::draw_lines() const
{
	Shape::draw_lines();

	if (color().visibility())	// draw closing line:
		fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
}

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	In_box x_in;
	In_box y_in;

	Menu menu;

	Vector_ref<Shape> v;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void make_shape(int sides_num);
	void make_circle();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	x_in{ Point{x_max() - 350, 0}, 50, 20, "x: " },
	y_in{Point{x_max() - 250, 0}, 50, 20, "y: "},
	menu{Point{x_max() - 70, 40}, 70, 20, Menu::vertical, ""}
{

	attach(next_button);
	attach(quit_button);
	attach(x_in);
	attach(y_in);
	menu.attach(new Button{ Point{0, 0}, 0, 0, "circle",
		[](Address, Address pw) {reference_to<My_window>(pw).make_circle(); } });
	menu.attach(new Button{ Point{0, 0}, 0, 0, "square",
		[](Address, Address pw) {reference_to<My_window>(pw).make_shape(4); } });
	menu.attach(new Button{ Point{0, 0}, 0, 0, "triangle",
		[](Address, Address pw) {reference_to<My_window>(pw).make_shape(3); } });
	menu.attach(new Button{ Point{0, 0}, 0, 0, "hexagon",
		[](Address, Address pw) {reference_to<My_window>(pw).make_shape(6); } });
	attach(menu);
}

void My_window::wait_for_button()
{
	while (!next_button_pushed && !quit_button_pushed)
	{
		Fl::wait();
	}
	if (next_button_pushed)
	{
		next_button_pushed = false;
		Fl::redraw();
	}
}

void My_window::cb_next(Address, Address pw)
{
	reference_to<My_window>(pw).next();
}

void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::next()
{
	next_button_pushed = true;
}

void My_window::quit()
{
	quit_button_pushed = true;
	hide();
}

void My_window::make_shape(int sides_num)
{
	Point center{ x_in.get_int(), y_in.get_int() };
	const int radius = 100;

	v.push_back(new Regular_polygon{ center, radius, sides_num });
	v[v.size() - 1].set_color(Color::black);
	attach(v[v.size() - 1]);

	redraw();
}

void My_window::make_circle()
{
	Point center{ x_in.get_int(), y_in.get_int() };
	const int radius = 100;

	v.push_back(new Circle{ center, radius });
	v[v.size() - 1].set_color(Color::black);
	attach(v[v.size() - 1]);

	redraw();
}

int main()
try
{
	My_window win{ Point{100, 100}, 600, 400, "My window" };
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