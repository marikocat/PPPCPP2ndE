#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Group {
	public:
		void add(Shape& shape) { v.push_back(shape); }
		void add(Shape* shape) { v.push_back(shape); }
		Shape& shape(int i) { return v[i]; }
		void move(int dx, int dy);
		void set_color(Color color);
		int size() const { return v.size(); }
	private:
		Vector_ref<Shape> v;
	};

	void Group::move(int dx, int dy)
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].move(dx, dy);
	}

	void Group::set_color(Color color)
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].set_color(color);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point {100, 100}, 1280, 800, "Group" };

	Group board;
	const int cell_num = 8;
	const int cell_size = win.y_max() / cell_num;
	for (int i = 0; i < cell_num; ++i)
		for (int j = 0; j < cell_num; ++j)
		{
			board.add(new Graph_lib::Rectangle{ Point{j * cell_size, i * cell_size}, cell_size, cell_size });
			board.shape(board.size() - 1).set_fill_color((i + j) % 2 == 0 ? Color::white : Color::black);
		}
	board.set_color(Color::black);

	Group white_checkers;
	int checker_radius = cell_size / 3;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
		{
			white_checkers.add(new Circle{ Point{cell_size / 2 + j * cell_size * 2 + (i % 2 == 0 ? cell_size : 0),
				cell_size / 2 + i * cell_size}, 
				checker_radius });
			white_checkers.shape(white_checkers.size() - 1).set_fill_color(Color::white);
		}
	white_checkers.set_color(Color::white);

	Group black_checkers;
	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 4; ++j)
		{
			black_checkers.add(new Circle{ Point{cell_size / 2 + j * cell_size * 2 + (i % 2 == 0 ? 0 : cell_size),
				cell_size * 5 + cell_size / 2 + i * cell_size},
				checker_radius });
			black_checkers.shape(black_checkers.size() - 1).set_fill_color(Color::yellow);
		}
	black_checkers.set_color(Color::black);

	for (int i = 0; i < board.size(); ++i)
		win.attach(board.shape(i));
	for (int i = 0; i < white_checkers.size(); ++i)
		win.attach(white_checkers.shape(i));
	for (int i = 0; i < black_checkers.size(); ++i)
		win.attach(black_checkers.shape(i));
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