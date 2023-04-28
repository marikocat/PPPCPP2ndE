#include "Gui.h"

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	Vector_ref<Function> v;
	In_box min_r_box;
	In_box max_r_box;
	In_box num_box;
	In_box x_scale_box;
	In_box y_scale_box;
	Menu functions_menu;

	Axis x;
	Axis y;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void graph_function(Fct f);
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	min_r_box{Point{40, 40}, 50, 20, "Min: "},
	max_r_box{Point{165, 40}, 50, 20, "Max: "},
	num_box{Point{290, 40}, 50, 20, "Count: "},
	x_scale_box{Point{415, 40}, 50, 20, "X scale: "},
	y_scale_box{Point{540, 40}, 50, 20, "Y scale: "},
	functions_menu{Point{190, 80}, 70, 20, Menu::horizontal, "Function"},
	x{ Axis::x, Point{20, 250}, 560, 560 / 20, "x axis"},
	y{Axis::y, Point{300, 380}, 240, 240 / 20, "y axis"}
{
	attach(next_button);
	attach(quit_button);
	attach(min_r_box);
	attach(max_r_box);
	attach(num_box);
	attach(x_scale_box);
	attach(y_scale_box);
	functions_menu.attach(new Button{ Point{0, 0}, 0, 0, "sin()",
		[](Address, Address pw) {reference_to<My_window>(pw).graph_function(sin); } });
	functions_menu.attach(new Button{ Point{0, 0}, 0, 0, "cos()",
		[](Address, Address pw) {reference_to<My_window>(pw).graph_function(cos); } });
	functions_menu.attach(new Button{ Point{0, 0}, 0, 0, "exp()",
		[](Address, Address pw) {reference_to<My_window>(pw).graph_function(exp); } });
	attach(functions_menu);
	x.set_color(Color::dark_red);
	y.set_color(Color::dark_red);
	attach(x);
	attach(y);
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

void My_window::graph_function(Fct f)
{
	string s = min_r_box.get_string() + " " + max_r_box.get_string() + " " +
		x_scale_box.get_string() + " " + y_scale_box.get_string();
	istringstream iss{ s };
	double min_r, max_r, xscale, yscale;
	iss >> min_r >> max_r >> xscale >> yscale;
	int count = num_box.get_int();

	v.push_back(new Function{ f, min_r, max_r, Point{300, 250}, count, xscale, yscale });
	v[v.size() - 1].set_color(rand() % 10);
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