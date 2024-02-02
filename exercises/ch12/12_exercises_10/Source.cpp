#include "Simple_window.h"
#include "Graph.h"

using namespace Graph_lib;

int main()
{
	const Point tl{ x_max() / 16 * 2, y_max() / 16 };
	Simple_window s_win(tl, x_max() * 3 / 4, y_max() * 7 / 8, "My window");

	const int box_w_s = s_win.x_max() / 8;
	const int box_w_m = s_win.x_max() / 6;
	const int box_w_l = s_win.x_max() / 4;
	const int box_h_s = s_win.y_max() / 24;
	const int box_h_m = box_h_s * 3 / 2;
	const int box_h_l = box_h_s * 5 / 2;
	const int box_shift = 5;
	const int padding = 10;
	const int label_size = 16;
	const int arrowhead_size = 6;

	Graph_lib::Rectangle fltk_h_box1{ Point{s_win.x_max() * 15 / 32, s_win.y_max() / 32}, box_w_m, box_h_m };
	fltk_h_box1.set_color(Color::black);
	fltk_h_box1.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_h_box2{ Point{s_win.x_max() * 15 / 32 + box_shift, s_win.y_max() / 32 + box_shift},
		box_w_m, box_h_m };
	fltk_h_box2.set_color(Color::black);
	fltk_h_box2.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_h_box3{ Point{s_win.x_max() * 15 / 32 + box_shift * 2, s_win.y_max() / 32 + box_shift * 2},
		box_w_m, box_h_m };
	fltk_h_box3.set_color(Color::black);
	fltk_h_box3.set_fill_color(Color::yellow);

	Text fltk_h_label{ Point{fltk_h_box3.point(0).x + padding * 6, fltk_h_box3.point(0).y + padding * 2}, "FLTK headers" };
	fltk_h_label.set_color(Color::black);
	fltk_h_label.set_font_size(label_size);

	s_win.attach(fltk_h_box1);
	s_win.attach(fltk_h_box2);
	s_win.attach(fltk_h_box3);
	s_win.attach(fltk_h_label);

	Graph_lib::Rectangle fltk_c_box1{ Point{s_win.x_max() * 25 / 32, s_win.y_max() / 8}, box_w_m, box_h_m };
	fltk_c_box1.set_color(Color::black);
	fltk_c_box1.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_c_box2{ Point{s_win.x_max() * 25 / 32 + box_shift, s_win.y_max() / 8 + box_shift},
		box_w_m, box_h_m };
	fltk_c_box2.set_color(Color::black);
	fltk_c_box2.set_fill_color(Color::yellow);

	Graph_lib::Rectangle fltk_c_box3{ Point{s_win.x_max() * 25 / 32 + box_shift * 2, s_win.y_max() / 8 + box_shift * 2}, box_w_m, box_h_m };
	fltk_c_box3.set_color(Color::black);
	fltk_c_box3.set_fill_color(Color::yellow);

	Text fltk_c_label{ Point{fltk_c_box3.point(0).x + padding * 8, fltk_c_box3.point(0).y + padding * 2}, "FLTK code" };
	fltk_c_label.set_color(Color::black);
	fltk_c_label.set_font_size(label_size);

	s_win.attach(fltk_c_box1);
	s_win.attach(fltk_c_box2);
	s_win.attach(fltk_c_box3);
	s_win.attach(fltk_c_label);

	Graph_lib::Rectangle point_h_box{ Point{s_win.x_max() / 8, s_win.y_max() / 8}, box_w_m, box_h_s };
	point_h_box.set_color(Color::black);
	point_h_box.set_fill_color(Color::yellow);

	Text point_h_label1{ Point{point_h_box.point(0).x, point_h_box.point(0).y - padding}, "Point.h:" };
	point_h_label1.set_color(Color::black);
	point_h_label1.set_font_size(label_size);
	point_h_label1.set_font(Font::helvetica_bold);

	Text point_h_label2{ Point{point_h_box.point(0).x + padding, point_h_box.point(0).y + padding * 2}, "struct Point { ... };" };
	point_h_label2.set_color(Color::black);
	point_h_label2.set_font_size(label_size);
	point_h_label2.set_font(Font::helvetica_bold);

	s_win.attach(point_h_box);
	s_win.attach(point_h_label1);
	s_win.attach(point_h_label2);

	Graph_lib::Rectangle win_h_box{ Point{s_win.x_max() * 14 / 32, s_win.y_max() * 10 / 32}, box_w_l, box_h_l };
	win_h_box.set_color(Color::black);
	win_h_box.set_fill_color(Color::yellow);

	Text win_h_label1{ Point{ win_h_box.point(0).x,
		win_h_box.point(0).y - padding }, "Window.h" };
	win_h_label1.set_color(Color::black);
	win_h_label1.set_font_size(label_size);
	win_h_label1.set_font(Font::helvetica_bold);

	Text win_h_label2{ Point{ win_h_box.point(0).x + padding,
		win_h_box.point(0).y + padding * 2 }, "// window interface:" };
	win_h_label2.set_color(Color::black);
	win_h_label2.set_font_size(label_size);

	Text win_h_label3{ Point{ win_h_box.point(0).x + padding,
		win_h_label2.point(0).y + padding * 2 },
		"class Window { ... };" };
	win_h_label3.set_color(Color::black);
	win_h_label3.set_font_size(label_size);
	win_h_label3.set_font(Font::helvetica_bold);

	Text win_h_label4{ Point{ win_h_box.point(0).x + padding,
		win_h_label3.point(0).y + padding * 2 }, "..." };
	win_h_label4.set_color(Color::black);
	win_h_label4.set_font_size(label_size);

	s_win.attach(win_h_box);
	s_win.attach(win_h_label1);
	s_win.attach(win_h_label2);
	s_win.attach(win_h_label3);
	s_win.attach(win_h_label4);

	Graph_lib::Rectangle graph_h_box{ Point{ point_h_box.point(0).x, s_win.y_max() * 14 / 32 }, box_w_l, box_h_l };
	graph_h_box.set_color(Color::black);
	graph_h_box.set_fill_color(Color::yellow);

	Text graph_h_label1{ Point{ graph_h_box.point(0).x,
		graph_h_box.point(0).y - padding }, "Graph.h" };
	graph_h_label1.set_color(Color::black);
	graph_h_label1.set_font_size(label_size);
	graph_h_label1.set_font(Font::helvetica_bold);

	Text graph_h_label2{ Point{ graph_h_box.point(0).x + padding,
		graph_h_box.point(0).y + padding * 2 }, "// graphing interface:" };
	graph_h_label2.set_color(Color::black);
	graph_h_label2.set_font_size(label_size);

	Text graph_h_label3{ Point{ graph_h_box.point(0).x + padding,
		graph_h_label2.point(0).y + padding * 2 },
		"struct Shape { ... };" };
	graph_h_label3.set_color(Color::black);
	graph_h_label3.set_font_size(label_size);
	graph_h_label3.set_font(Font::helvetica_bold);

	Text graph_h_label4{ Point{ graph_h_box.point(0).x + padding,
		graph_h_label3.point(0).y + padding * 2 }, "..." };
	graph_h_label4.set_color(Color::black);
	graph_h_label4.set_font_size(label_size);

	s_win.attach(graph_h_box);
	s_win.attach(graph_h_label1);
	s_win.attach(graph_h_label2);
	s_win.attach(graph_h_label3);
	s_win.attach(graph_h_label4);

	Graph_lib::Rectangle gui_h_box{ Point{ s_win.x_max() * 20 / 32, s_win.y_max() / 2 }, box_w_l, box_h_l };
	gui_h_box.set_color(Color::black);
	gui_h_box.set_fill_color(Color::yellow);

	Text gui_h_label1{ Point{ gui_h_box.point(0).x,
		gui_h_box.point(0).y - padding }, "GUI.h" };
	gui_h_label1.set_color(Color::black);
	gui_h_label1.set_font_size(label_size);
	gui_h_label1.set_font(Font::helvetica_bold);

	Text gui_h_label2{ Point{ gui_h_box.point(0).x + padding,
		gui_h_box.point(0).y + padding * 4 }, "// GUI interface:" };
	gui_h_label2.set_color(Color::black);
	gui_h_label2.set_font_size(label_size);

	Text gui_h_label3{ Point{ gui_h_box.point(0).x + padding,
		gui_h_label2.point(0).y + padding * 2 }, "struct In_box { ... };" };
	gui_h_label3.set_color(Color::black);
	gui_h_label3.set_font_size(label_size);
	gui_h_label3.set_font(Font::helvetica_bold);

	Text gui_h_label4{ Point{ gui_h_box.point(0).x + padding,
		gui_h_label3.point(0).y + padding * 2 }, "..." };
	gui_h_label4.set_color(Color::black);
	gui_h_label4.set_font_size(label_size);

	s_win.attach(gui_h_box);
	s_win.attach(gui_h_label1);
	s_win.attach(gui_h_label2);
	s_win.attach(gui_h_label3);
	s_win.attach(gui_h_label4);

	Graph_lib::Rectangle window_c_box{ Point{ s_win.x_max() * 10 / 32,
		s_win.y_max() * 19 / 32 }, box_w_m, box_h_s };
	window_c_box.set_color(Color::black);
	window_c_box.set_fill_color(Color::yellow);

	Text window_c_label1{ Point{ window_c_box.point(0).x,
		window_c_box.point(0).y - padding }, "Window.cpp" };
	window_c_label1.set_color(Color::black);
	window_c_label1.set_font_size(label_size);
	window_c_label1.set_font(Font::helvetica_bold);

	Text window_c_label2{ Point{ window_c_box.point(0).x + padding,
		window_c_box.point(0).y + padding * 2 }, "Window code" };
	window_c_label2.set_color(Color::black);
	window_c_label2.set_font_size(label_size);
	window_c_label2.set_font(Font::helvetica_bold);

	s_win.attach(window_c_box);
	s_win.attach(window_c_label1);
	s_win.attach(window_c_label2);

	Graph_lib::Rectangle graph_c_box{ Point{ s_win.x_max() * 2 / 32,
		s_win.y_max() * 22 / 32 }, box_w_s, box_h_s };
	graph_c_box.set_color(Color::black);
	graph_c_box.set_fill_color(Color::yellow);

	Text graph_c_label1{ Point{ graph_c_box.point(0).x,
		graph_c_box.point(0).y - padding }, "Graph.cpp" };
	graph_c_label1.set_color(Color::black);
	graph_c_label1.set_font_size(label_size);
	graph_c_label1.set_font(Font::helvetica_bold);

	Text graph_c_label2{ Point{ graph_c_box.point(0).x + padding,
		graph_c_box.point(0).y + padding * 2 }, "Graph code" };
	graph_c_label2.set_color(Color::black);
	graph_c_label2.set_font_size(label_size);
	graph_c_label2.set_font(Font::helvetica_bold);

	s_win.attach(graph_c_box);
	s_win.attach(graph_c_label1);
	s_win.attach(graph_c_label2);

	Graph_lib::Rectangle gui_c_box{ Point{ s_win.x_max() * 24 / 32,
		graph_c_box.point(0).y }, box_w_s, box_h_s };
	gui_c_box.set_color(Color::black);
	gui_c_box.set_fill_color(Color::yellow);

	Text gui_c_label1{ Point{ gui_c_box.point(0).x,
		gui_c_box.point(0).y - padding }, "GUI.cpp" };
	gui_c_label1.set_color(Color::black);
	gui_c_label1.set_font_size(label_size);
	gui_c_label1.set_font(Font::helvetica_bold);

	Text gui_c_label2{ Point{ gui_c_box.point(0).x + padding,
		gui_c_box.point(0).y + padding * 2 }, "GUI code" };
	gui_c_label2.set_color(Color::black);
	gui_c_label2.set_font_size(label_size);
	gui_c_label2.set_font(Font::helvetica_bold);

	s_win.attach(gui_c_box);
	s_win.attach(gui_c_label1);
	s_win.attach(gui_c_label2);

	Graph_lib::Rectangle s_win_h_box{ Point{ s_win.x_max() * 13 / 32,
		s_win.y_max() * 23 / 32 }, box_w_l, box_h_l };
	s_win_h_box.set_color(Color::black);
	s_win_h_box.set_fill_color(Color::yellow);

	Text s_win_h_label1{ Point{ s_win_h_box.point(0).x,
		s_win_h_box.point(0).y - padding }, "Simple_window.h" };
	s_win_h_label1.set_color(Color::black);
	s_win_h_label1.set_font_size(label_size);
	s_win_h_label1.set_font(Font::helvetica_bold);

	Text s_win_h_label2{ Point{ s_win_h_box.point(0).x + padding,
		s_win_h_box.point(0).y + padding * 2 }, "// window interface:" };
	s_win_h_label2.set_color(Color::black);
	s_win_h_label2.set_font_size(label_size);

	Text s_win_h_label3{ Point{ s_win_h_box.point(0).x + padding,
		s_win_h_label2.point(0).y + padding * 2 },
		"class Simple_window { ... };" };
	s_win_h_label3.set_color(Color::black);
	s_win_h_label3.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	Text s_win_h_label4{ Point{ s_win_h_box.point(0).x + padding,
		s_win_h_label3.point(0).y + padding * 2 }, "..." };
	s_win_h_label4.set_color(Color::black);
	s_win_h_label4.set_font_size(label_size);

	s_win.attach(s_win_h_box);
	s_win.attach(s_win_h_label1);
	s_win.attach(s_win_h_label2);
	s_win.attach(s_win_h_label3);
	s_win.attach(s_win_h_label4);

	Graph_lib::Rectangle ch_12_c_box{ Point{ s_win.x_max() * 6 / 32,
		s_win.y_max() * 28 / 32 }, box_w_l, box_h_l };
	ch_12_c_box.set_color(Color::black);
	ch_12_c_box.set_fill_color(Color::yellow);

	Text ch_12_c_label1{ Point{ ch_12_c_box.point(0).x,
		ch_12_c_box.point(0).y - padding }, "Chapter12.cpp" };
	ch_12_c_label1.set_color(Color::black);
	ch_12_c_label1.set_font_size(label_size);
	ch_12_c_label1.set_font(Font::helvetica_bold);

	Text ch_12_c_label2{ Point{ ch_12_c_box.point(0).x + padding,
		ch_12_c_box.point(0).y + padding * 2 }, "#include \"Graph.h\"" };
	ch_12_c_label2.set_color(Color::black);
	ch_12_c_label2.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	Text ch_12_c_label3{ Point{ ch_12_c_box.point(0).x + padding,
		ch_12_c_label2.point(0).y + padding * 2 },
		"#include \"Simple_window.h\"" };
	ch_12_c_label3.set_color(Color::black);
	ch_12_c_label3.set_font_size(label_size);
	ch_12_c_label3.set_font(Font::helvetica_bold);

	Text ch_12_c_label4{ Point{ ch_12_c_box.point(0).x + padding,
		ch_12_c_label3.point(0).y + padding * 2 }, "int main() { ... }" };
	ch_12_c_label4.set_color(Color::black);
	ch_12_c_label4.set_font_size(label_size);
	s_win_h_label3.set_font(Font::helvetica_bold);

	s_win.attach(ch_12_c_box);
	s_win.attach(ch_12_c_label1);
	s_win.attach(ch_12_c_label2);
	s_win.attach(ch_12_c_label3);
	s_win.attach(ch_12_c_label4);

	s_win.wait_for_button();


	Line arrow1{ Point{fltk_c_box1.point(0).x, fltk_c_box1.point(0).y + box_h_m / 2},
		Point{fltk_h_box3.point(0).x + box_w_m, fltk_h_box3.point(0).y + box_h_m / 2} };
	arrow1.set_color(Color::black);

	Graph_lib::Polygon arrowhead1;
	arrowhead1.add(Point{ arrow1.point(1) });
	arrowhead1.add(Point{ arrow1.point(1).x + arrowhead_size,
		arrow1.point(1).y + arrowhead_size / 2 });
	arrowhead1.add(Point{ arrow1.point(1).x + arrowhead_size,
		arrow1.point(1).y - arrowhead_size / 2 });
	arrowhead1.set_color(Color::black);
	arrowhead1.set_fill_color(Color::black);

	s_win.attach(arrow1);
	s_win.attach(arrowhead1);

	Line arrow2{ Point{ graph_h_box.point(0).x + box_w_l / 2,
		graph_h_box.point(0).y }, Point{ fltk_h_box3.point(0).x + box_shift,
		fltk_h_box3.point(0).y + box_h_m } };
	arrow2.set_color(Color::black);

	Graph_lib::Polygon arrowhead2;
	arrowhead2.add(Point{ arrow2.point(1) });
	arrowhead2.add(Point{ arrow2.point(1).x + arrowhead_size / 2,
		arrow2.point(1).y + arrowhead_size });
	arrowhead2.add(Point{ arrow2.point(1).x - arrowhead_size / 2,
		arrow2.point(1).y + arrowhead_size });
	arrowhead2.set_color(Color::black);
	arrowhead2.set_fill_color(Color::black);

	s_win.attach(arrow2);
	s_win.attach(arrowhead2);

	Line arrow3{ Point{ win_h_box.point(0).x + box_w_l / 2,
		win_h_box.point(0).y },
		Point{ win_h_box.point(0).x + box_w_l / 2,
		fltk_h_box3.point(0).y + box_h_m } };
	arrow3.set_color(Color::black);

	Graph_lib::Polygon arrowhead3;
	arrowhead3.add(Point{ arrow3.point(1) });
	arrowhead3.add(Point{ arrow3.point(1).x + arrowhead_size / 2,
		arrow3.point(1).y + arrowhead_size });
	arrowhead3.add(Point{ arrow3.point(1).x - arrowhead_size / 2,
		arrow3.point(1).y + arrowhead_size });
	arrowhead3.set_color(Color::black);
	arrowhead3.set_fill_color(Color::black);

	s_win.attach(arrow3);
	s_win.attach(arrowhead3);

	Line arrow4{ Point{ gui_h_box.point(0).x + box_w_l * 2 / 3,
		gui_h_box.point(0).y },
		Point{ fltk_h_box3.point(0).x + box_w_m * 3 / 4,
		fltk_h_box3.point(0).y + box_h_m } };
	arrow4.set_color(Color::black);

	Graph_lib::Polygon arrowhead4;
	arrowhead4.add(Point{ arrow4.point(1) });
	arrowhead4.add(Point{ arrow4.point(1).x + arrowhead_size / 2,
		arrow4.point(1).y + arrowhead_size });
	arrowhead4.add(Point{ arrow4.point(1).x - arrowhead_size / 2,
		arrow4.point(1).y + arrowhead_size });
	arrowhead4.set_color(Color::black);
	arrowhead4.set_fill_color(Color::black);

	s_win.attach(arrow4);
	s_win.attach(arrowhead4);

	Line arrow5{ Point{ graph_h_box.point(0).x + box_w_l / 2,
		graph_h_box.point(0).y },
		Point{ graph_h_box.point(0).x + box_w_l / 2,
		point_h_box.point(0).y + box_h_s } };
	arrow5.set_color(Color::black);

	Graph_lib::Polygon arrowhead5;
	arrowhead5.add(Point{ arrow5.point(1) });
	arrowhead5.add(Point{ arrow5.point(1).x - arrowhead_size / 2,
		arrow5.point(1).y + arrowhead_size });
	arrowhead5.add(Point{ arrow5.point(1).x + arrowhead_size / 2,
		arrow5.point(1).y + arrowhead_size });
	arrowhead5.set_color(Color::black);
	arrowhead5.set_fill_color(Color::black);

	s_win.attach(arrow5);
	s_win.attach(arrowhead5);

	Line arrow6{ Point{win_h_box.point(0).x + box_shift * 2,
		win_h_box.point(0).y},
		Point{ point_h_box.point(0).x + box_w_m - box_shift * 2,
		point_h_box.point(0).y + box_h_s } };
	arrow6.set_color(Color::black);

	Graph_lib::Polygon arrowhead6;
	arrowhead6.add(Point{ arrow6.point(1) });
	arrowhead6.add(Point{ arrow6.point(1).x + arrowhead_size / 2,
		arrow6.point(1).y + arrowhead_size });
	arrowhead6.add(Point{ arrow6.point(1).x - arrowhead_size / 2,
		arrow6.point(1).y + arrowhead_size });
	arrowhead6.set_color(Color::black);
	arrowhead6.set_fill_color(Color::black);

	s_win.attach(arrow6);
	s_win.attach(arrowhead6);

	Line arrow7{ Point{ window_c_box.point(0).x + box_w_m * 3 / 4,
		window_c_box.point(0).y },
		Point{ win_h_box.point(0).x + box_w_l * 1 / 4,
		win_h_box.point(0).y + box_h_l } };
	arrow7.set_color(Color::black);

	Graph_lib::Polygon arrowhead7;
	arrowhead7.add(Point{ arrow7.point(1) });
	arrowhead7.add(Point{ arrow7.point(1).x - arrowhead_size / 2,
		arrow7.point(1).y + arrowhead_size });
	arrowhead7.add(Point{ arrow7.point(1).x + arrowhead_size / 2,
		arrow7.point(1).y + arrowhead_size });
	arrowhead7.set_color(Color::black);
	arrowhead7.set_fill_color(Color::black);

	s_win.attach(arrow7);
	s_win.attach(arrowhead7);

	Line arrow8{ Point{ s_win_h_box.point(0).x + box_w_l * 2 / 3,
		s_win_h_box.point(0).y },
		Point{ win_h_box.point(0).x + box_w_l / 2,
		win_h_box.point(0).y + box_h_l } };
	arrow8.set_color(Color::black);

	Graph_lib::Polygon arrowhead8;
	arrowhead8.add(Point{ arrow8.point(1) });
	arrowhead8.add(Point{ arrow8.point(1).x - arrowhead_size / 2,
		arrow8.point(1).y + arrowhead_size });
	arrowhead8.add(Point{ arrow8.point(1).x + arrowhead_size / 2,
		arrow8.point(1).y + arrowhead_size });
	arrowhead8.set_color(Color::black);
	arrowhead8.set_fill_color(Color::black);

	s_win.attach(arrow8);
	s_win.attach(arrowhead8);

	Line arrow9{ Point{ gui_h_box.point(0).x + box_w_l * 2 / 3,
		gui_h_box.point(0).y }, Point{ win_h_box.point(0).x + box_w_l - box_shift * 2,
		win_h_box.point(0).y + box_h_l } };
	arrow9.set_color(Color::black);

	Graph_lib::Polygon arrowhead9;
	arrowhead9.add(Point{ arrow9.point(1) });
	arrowhead9.add(Point{ arrow9.point(1).x + arrowhead_size / 2,
		arrow9.point(1).y + arrowhead_size });
	arrowhead9.add(Point{ arrow9.point(1).x - arrowhead_size / 2,
		arrow9.point(1).y + arrowhead_size });
	arrowhead9.set_color(Color::black);
	arrowhead9.set_fill_color(Color::black);

	s_win.attach(arrow9);
	s_win.attach(arrowhead9);

	Line arrow10{ Point{ graph_c_box.point(0).x + box_w_s * 3 / 4,
		graph_c_box.point(0).y },
		Point{ graph_h_box.point(0).x + box_w_l / 2,
		graph_h_box.point(0).y + box_h_l } };
	arrow10.set_color(Color::black);

	Graph_lib::Polygon arrowhead10;
	arrowhead10.add(Point{ arrow10.point(1) });
	arrowhead10.add(Point{ arrow10.point(1).x - arrowhead_size / 2,
		arrow10.point(1).y + arrowhead_size });
	arrowhead10.add(Point{ arrow10.point(1).x + arrowhead_size / 2,
		arrow10.point(1).y + arrowhead_size });
	arrowhead10.set_color(Color::black);
	arrowhead10.set_fill_color(Color::black);

	s_win.attach(arrow10);
	s_win.attach(arrowhead10);

	Line arrow11{ Point{ ch_12_c_box.point(0).x + box_w_l * 2 / 3,
		ch_12_c_box.point(0).y },
		Point{ graph_h_box.point(0).x + box_w_l * 9 / 16,
		graph_h_box.point(0).y + box_h_l } };
	arrow11.set_color(Color::black);

	Graph_lib::Polygon arrowhead11;
	arrowhead11.add(Point{ arrow11.point(1) });
	arrowhead11.add(Point{ arrow11.point(1).x - arrowhead_size / 2,
		arrow11.point(1).y + arrowhead_size });
	arrowhead11.add(Point{ arrow11.point(1).x + arrowhead_size / 2,
		arrow11.point(1).y + arrowhead_size });
	arrowhead11.set_color(Color::black);
	arrowhead11.set_fill_color(Color::black);

	s_win.attach(arrow11);
	s_win.attach(arrowhead11);

	Line arrow12{ Point{ s_win_h_box.point(0).x + box_w_l * 2 / 3,
		s_win_h_box.point(0).y }, Point{gui_h_box.point(0).x + box_shift * 2,
		gui_h_box.point(0).y + box_h_l } };
	arrow12.set_color(Color::black);

	Graph_lib::Polygon arrowhead12;
	arrowhead12.add(Point{ arrow12.point(1) });
	arrowhead12.add(Point{ arrow12.point(1).x + arrowhead_size / 2,
		arrow12.point(1).y + arrowhead_size });
	arrowhead12.add(Point{ arrow12.point(1).x - arrowhead_size / 2,
		arrow12.point(1).y + arrowhead_size });
	arrowhead12.set_color(Color::black);
	arrowhead12.set_fill_color(Color::black);

	s_win.attach(arrow12);
	s_win.attach(arrowhead12);

	Line arrow13{ Point{ gui_c_box.point(0).x + box_w_s * 3 / 4,
		gui_c_box.point(0).y }, Point{gui_h_box.point(0).x + box_w_l / 2,
		gui_h_box.point(0).y + box_h_l } };
	arrow13.set_color(Color::black);

	Graph_lib::Polygon arrowhead13;
	arrowhead13.add(Point{ arrow13.point(1) });
	arrowhead13.add(Point{ arrow13.point(1).x + arrowhead_size / 2,
		arrow13.point(1).y + arrowhead_size });
	arrowhead13.add(Point{ arrow13.point(1).x - arrowhead_size / 2,
		arrow13.point(1).y + arrowhead_size });
	arrowhead13.set_color(Color::black);
	arrowhead13.set_fill_color(Color::black);

	s_win.attach(arrow13);
	s_win.attach(arrowhead13);

	Line arrow14{ Point{ ch_12_c_box.point(0).x + box_w_l * 2 / 3,
		ch_12_c_box.point(0).y }, Point{s_win_h_box.point(0).x + box_shift * 2,
		s_win_h_box.point(0).y + box_h_l } };
	arrow14.set_color(Color::black);

	Graph_lib::Polygon arrowhead14;
	arrowhead14.add(Point{ arrow14.point(1) });
	arrowhead14.add(Point{ arrow14.point(1).x + arrowhead_size / 2,
		arrow14.point(1).y + arrowhead_size });
	arrowhead14.add(Point{ arrow14.point(1).x - arrowhead_size / 2,
		arrow14.point(1).y + arrowhead_size });
	arrowhead14.set_color(Color::black);
	arrowhead14.set_fill_color(Color::black);

	s_win.attach(arrow14);
	s_win.attach(arrowhead14);

	s_win.wait_for_button();
}