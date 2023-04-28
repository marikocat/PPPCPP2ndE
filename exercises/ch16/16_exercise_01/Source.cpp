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

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{xy, w, h, title},
	next_button{Point{x_max() - 150, 0}, 70, 20, "Next", cb_next},
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{false}
{
	attach(next_button);
	attach(quit_button);
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

int main()
try
{
	My_window win{ Point{100, 100}, 600, 400, "My window" };
	
	Circle c{ Point{150, 150}, 100 };
	c.set_color(Color::black);
	win.attach(c);
	win.wait_for_button();

	win.detach(c);
	Graph_lib::Rectangle r{ Point{100, 100}, 200, 200 };
	r.set_color(Color::black);
	win.attach(r);
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