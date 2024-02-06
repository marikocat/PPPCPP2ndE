#include "Simple_window.h"
#include "Graph.h"

int main()
{
	Simple_window win{ Point{100, 100}, 320, 320, "RGB color chart" };

	const int num = 16;
	const int rect_size = win.y_max() / num;

	Vector_ref<Graph_lib::Rectangle> rects;
	for (int i = 0; i < num; ++i)
		for (int j = 0; j < num; ++j)
		{
			rects.push_back(new Graph_lib::Rectangle{ {i  * rect_size, j * rect_size}, rect_size, rect_size });
			rects[rects.size() - 1].set_color(Color::black);
			rects[rects.size() - 1].set_fill_color(fl_rgb_color(i * num, j * num, i * j));
			std::cout << i * num << " " << j * num << " " << i * j << "\n";
			win.attach(rects[rects.size() - 1]);
		}
	win.wait_for_button();
}