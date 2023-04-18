#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Binary_tree : public Shape {
	public:
		Binary_tree(Point tl, int win_width, int win_height, int levels);

		void draw_lines() const override;

		void move(int dx, int dy);
		void set_color(Color color);

		int width() const { return w; }
		int height() const { return h; }
		int levels_num() const { return l; }
	private:
		int w;
		int h;
		int l;
		Vector_ref<Circle> nodes;
		Lines lines;
	};

	Binary_tree::Binary_tree(Point tl, int win_width, int win_height, int levels) 
		: w{ win_width }, h{ win_height }, l{ levels }
	{
		if (levels < 0) error("Invalid number of levels");

		add(tl);
		
		int node_width = win_width / pow(2, levels);
		int node_height = win_height / levels / 2;
		int node_r;
		if (node_width < node_height) node_r = node_width / 2;
		else node_r = node_height / 2;

		for (int i = 0; i < levels; ++i)
			for (int j = 0; j < pow(2, i); ++j)
			{
				nodes.push_back(new Circle{ Point{point(0).x + int(win_width / pow(2, i) / 2 * (1 + j * 2)), 
					point(0).y + node_r * 2 + i * node_r * 4}, node_r });
				
				if (i > 0)
				{
					lines.add(Point{ nodes[nodes.size() - 1].center().x, nodes[nodes.size() - 1].center().y - node_r },
						Point{ nodes[nodes.size() - 1].center().x + int(win_width / pow(2, i) / 2) * (j % 2 == 0 ? 1 : -1), nodes[nodes.size() - 1].center().y - node_r * 3 });
				}
			}
	}

	void Binary_tree::draw_lines() const
	{
		for (int i = 0; i < nodes.size(); ++i)
			nodes[i].draw();

		lines.draw();
	}

	void Binary_tree::move(int dx, int dy)
	{
		for (int i = 0; i < nodes.size(); ++i)
			nodes[i].move(dx, dy);

		lines.move(dx, dy);
	}

	void Binary_tree::set_color(Color color)
	{
		Shape::set_color(color);

		for (int i = 0; i < nodes.size(); ++i)
			nodes[i].set_color(color);

		lines.set_color(color);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 600, "Graph" };

	Binary_tree b_tree{ Point{0, 0}, 600, 600, 5 };
	b_tree.set_color(Color::black);

	win.attach(b_tree);
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