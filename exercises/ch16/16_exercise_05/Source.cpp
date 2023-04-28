#include "Gui.h"

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;

	Button quit_button;
	bool quit_button_pushed;

	Circle c;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	c{Point{100, 100}, 100}
{
	c.set_color(Color::black);
	attach(next_button);
	attach(quit_button);
	attach(c);
}

void My_window::wait_for_button()
{
	while (!quit_button_pushed) Fl::wait();
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
	cout << "Enter a coordinate pair:\n";
	int x, y;
	cin >> x >> y;
	if (!cin) error("invalid input");

	c.move(x - c.center().x, y - c.center().y);
	redraw();
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