#include "Gui.h"

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button img_button;
	Image img;

	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void move_img_button();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	img_button{Point{0, 0}, 200, 200, "",
		[](Address, Address pw) {reference_to<My_window>(pw).move_img_button(); } },
	img{ Point{0, 0}, "img.jpg"},
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false }
{
	attach(img_button);
	attach(img);
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

void My_window::move_img_button()
{
	int x = randint(0, x_max() - 200);
	int y = randint(0, y_max() - 200);
	img_button.move(x - img_button.loc.x, y - img_button.loc.y);
	img.move(x - img.point(0).x, y - img.point(0).y);
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