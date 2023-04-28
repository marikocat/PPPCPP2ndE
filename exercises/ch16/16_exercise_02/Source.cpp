#include "GUI.h"

using namespace Graph_lib;

struct Checker_window : Window {
	Checker_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	const int board_size = 4;
	Vector_ref<Button> checkers;
	Graph_lib::Rectangle colored_rect;

	Out_box xy_out;

	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void move_colored_rect(int x, int y);
};

Checker_window::Checker_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	colored_rect{ Point{0, 0}, h / board_size, h / board_size },
	xy_out{ Point{x_max() - 120, 100}, 100, 20, "Point: "},
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false }	
{
	const int checker_size = h / board_size;
	for (int i = 0; i < board_size; ++i)
		for (int j = 0; j < board_size; ++j)
		{
			checkers.push_back(new Button{ Point{j * checker_size, i * checker_size},
				checker_size, checker_size, "press",
				[](Address pc, Address pw) { reference_to<Checker_window>(pw)
					.move_colored_rect(reference_to<Fl_Widget>(pc).x(), reference_to<Fl_Widget>(pc).y()); } });
			attach(checkers[checkers.size() - 1]);
		}
	colored_rect.set_color(Color::invisible);
	attach(colored_rect);
	attach(xy_out);
	xy_out.put("Not pressed");
	attach(next_button);
	attach(quit_button);
}

void Checker_window::wait_for_button()
{
	while (!next_button_pushed && !quit_button_pushed)
	{
		Fl::wait();
	}
	if (next_button_pushed)
	{
		next_button_pushed = false;
		cout << "before redraw()\n";
		Fl::redraw();
		cout << "after redraw()\n";
	}
}

void Checker_window::cb_next(Address, Address pw)
{
	reference_to<Checker_window>(pw).next();
}

void Checker_window::cb_quit(Address, Address pw)
{
	reference_to<Checker_window>(pw).quit();
}

void Checker_window::next()
{
	next_button_pushed = true;
}

void Checker_window::quit()
{
	quit_button_pushed = true;
	hide();
}

void Checker_window::move_colored_rect(int x, int y)
{
	ostringstream oss;
	oss << '(' << x << ',' << y << ')';
	xy_out.put(oss.str());

	colored_rect.move(x - colored_rect.point(0).x, y - colored_rect.point(0).y);
	colored_rect.set_fill_color(Color::magenta);
	redraw();
}

int main()
try
{
	Checker_window win{ Point{100, 100}, 600, 400, "My window" };

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