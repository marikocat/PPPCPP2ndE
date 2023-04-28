#include "Gui.h"
#include <chrono>
#include <thread>

using namespace Graph_lib;

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button quit_button;
	bool quit_button_pushed;

	const int img_size = 200;
	int img_dx = 5;
	Image img;

	Button start_button;
	bool started;
	Button stop_button;

	static void cb_quit(Address, Address);
	void quit();

	void start();
	void stop();

	void fly();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	img{Point{0, h / 2}, "plane.jpg"},
	start_button{ Point{x_max() - 150, 40}, 70, 20, "Start",
		[](Address, Address pw) {reference_to<My_window>(pw).start(); } },
	started{ false },
	stop_button{ Point{x_max() - 70, 40}, 70, 20, "Stop",
		[](Address, Address pw) {reference_to<My_window>(pw).stop(); } }
{
	attach(quit_button);
	attach(img);
	attach(start_button);
	attach(stop_button);
}

void My_window::wait_for_button()
{
	while (!quit_button_pushed)
	{
		Fl::wait();
		if (started) fly();
	}
}

void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::quit()
{
	quit_button_pushed = true;
	hide();
}

void My_window::start()
{
	started = true;
}

void My_window::stop()
{
	started = false;
}

void My_window::fly()
{
	if (img.point(0).x + img_size > x_max() || img.point(0).x < 0)
	{
		cout << "changed sign\n";
		img_dx = -img_dx;
	}
	img.move(img_dx, 0);
	redraw();
	this_thread::sleep_for(chrono::milliseconds(10));
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