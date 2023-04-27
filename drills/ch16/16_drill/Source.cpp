#include "Window.h"
#include "Graph.h"
#include "Gui.h"

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);
private:
	Open_polyline lines;

	Button next_button;
	Button quit_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	Menu color_menu;
	Button menu_button;

	Menu style_menu;
	Button style_menu_button;

	void change(Color c) { lines.set_color(c); }
	void change_style(Line_style ls) { lines.set_style(ls); }
	void hide_menu() { color_menu.hide(); menu_button.show(); }
	void hide_style_menu() { style_menu.hide(); style_menu_button.show(); }

	// actions invoked by callbacks
	void next();
	void quit();
	void red_pressed() { change(Color::red); hide_menu(); }
	void blue_pressed() { change(Color::blue); hide_menu(); }
	void black_pressed() { change(Color::black); hide_menu(); }
	void menu_pressed() { menu_button.hide(); color_menu.show(); }
	void solid_pressed() { change_style(Line_style::solid); hide_style_menu(); }
	void dash_pressed() { change_style(Line_style::dash); hide_style_menu(); }
	void dot_pressed() { change_style(Line_style::dot); hide_style_menu(); }
	void style_menu_pressed() { style_menu_button.hide(); style_menu.show(); }

	//callback functions
	static void cb_red(Address, Address);
	static void cb_blue(Address, Address);
	static void cb_black(Address, Address);
	static void cb_menu(Address, Address);
	static void cb_solid(Address, Address);
	static void cb_dashed(Address, Address);
	static void cb_dotted(Address, Address);
	static void cb_style_menu(Address, Address);
};

Lines_window::Lines_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next point",
		[](Address, Address pw) {reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to <Lines_window>(pw).quit(); } },
	next_x{ Point{x_max() - 310, 0}, 50, 20, "next x: " },
	next_y{ Point{x_max() - 210, 0}, 50, 20, "next y: " },
	xy_out{ Point{100, 0}, 100, 20, "current (x,y): " },
	color_menu{ Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color" },
	menu_button{ Point{x_max() - 80, 30}, 80, 20, "color menu", cb_menu },
	style_menu{ Point{x_max() - 150, 40}, 70, 20, Menu::vertical, "style" },
	style_menu_button{ Point{x_max() - 160, 30}, 80, 20, "style menu", cb_style_menu }
{
	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	xy_out.put("no point");

	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "red", cb_red });
	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "blue", cb_blue });
	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "black", cb_black });
	attach(color_menu);
	color_menu.hide();
	attach(menu_button);

	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "solid", cb_solid });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dash", cb_dashed });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dot", cb_dotted });
	attach(style_menu);
	style_menu.hide();
	attach(style_menu_button);

	attach(lines);
}

void Lines_window::quit()
{
	hide();
}

void Lines_window::next()
{
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x, y });

	// update current position readout:
	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	redraw();
}

void Lines_window::cb_red(Address, Address pw)      // "the usual"
{
	reference_to<Lines_window>(pw).red_pressed();
}

//------------------------------------------------------------------------------

void Lines_window::cb_blue(Address, Address pw)     // "the usual"
{
	reference_to<Lines_window>(pw).blue_pressed();
}

//------------------------------------------------------------------------------

void Lines_window::cb_black(Address, Address pw)    // "the usual"
{
	reference_to<Lines_window>(pw).black_pressed();
}

void Lines_window::cb_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).menu_pressed();
}

void Lines_window::cb_solid(Address, Address pw)
{
	reference_to<Lines_window>(pw).solid_pressed();
}

void Lines_window::cb_dashed(Address, Address pw)
{
	reference_to<Lines_window>(pw).dash_pressed();
}

void Lines_window::cb_dotted(Address, Address pw)
{
	reference_to<Lines_window>(pw).dot_pressed();
}

void Lines_window::cb_style_menu(Address, Address pw)
{
	reference_to<Lines_window>(pw).style_menu_pressed();
}

int main()
try
{
	Lines_window win{ Point{100, 100}, 600, 400, "lines" };
	return gui_main();
	// gui_main() returns function int Fl::run();
	// As long as any windows are displayed Fl::run() calls Fl::wait() repeatedly.
	// When all the windows are closed it returns zero (supposedly it would return non - zero on any errors, 
	// but FLTK calls exit directly for these). A normal program will end main() with return Fl::run();.
}
catch (exception& e)
{
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Some exception\n";
	return 2;
}