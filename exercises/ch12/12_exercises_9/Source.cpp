#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	Simple_window s_win{ Point{100, 100}, 600, 700, "Dvemid" };
	Image img{ Point{0, 20}, "pIMG.jpg" };
	//img.set_mask(Point{ 50, 50 }, 500, 500);

	Text caption(Point{ 250, 650 }, "Dvemid");
	caption.set_color(Color::black);
	caption.set_font(Font::courier_italic);
	caption.set_font_size(16);
	s_win.attach(caption);

	s_win.attach(img);

	s_win.wait_for_button();
}