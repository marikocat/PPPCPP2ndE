#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Binary_tree : public Shape {
	public:
		Binary_tree(Point tl, int win_width, int win_height, int levels);

		virtual void set_nodes();

		void draw_lines() const override;

		void move(int dx, int dy);
		void set_color(Color color);

		int width() const { return w; }
		int height() const { return h; }
		int levels_num() const { return l; }
	protected:
		int w;
		int h;
		int l;
		int node_r;
		Vector_ref<Shape> nodes;
		Lines lines;
	};

	Binary_tree::Binary_tree(Point tl, int win_width, int win_height, int levels)
		: w{ win_width }, h{ win_height }, l{ levels }
	{
		if (levels < 0) error("Invalid number of levels");

		add(tl);
		int node_width = w / pow(2, l);
		int node_height = h / (l * 2);
		if (node_width < node_height) node_r = node_width / 2;
		else node_r = node_height / 2;
	}

	void Binary_tree::set_nodes()
	{
		for (int i = 0; i < l; ++i)
			for (int j = 0; j < pow(2, i); ++j)
			{
				nodes.push_back(new Circle{ Point{point(0).x + int(w / pow(2, i) / 2 * (1 + j * 2)),
					point(0).y + node_r * 2 + i * node_r * 4}, node_r });

				if (i > 0)
				{
					lines.add(Point{ nodes[nodes.size() - 1].point(0).x + node_r,
						nodes[nodes.size() - 1].point(0).y },
						Point{ nodes[nodes.size() - 1].point(0).x + node_r + int(w / pow(2, i) / 2) * (j % 2 == 0 ? 1 : -1),
						nodes[nodes.size() - 1].point(0).y - node_r * 2 });
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

	class Binary_tree_sq : public Binary_tree {
	public:
		Binary_tree_sq(Point tl, int win_width, int win_height, int levels) :
			Binary_tree{tl, win_width, win_height, levels} {}

		void set_nodes() override;
	};

	void Binary_tree_sq::set_nodes()
	{
		for (int i = 0; i < l; ++i)
			for (int j = 0; j < pow(2, i); ++j)
			{
				nodes.push_back(new Graph_lib::Rectangle{ Point{point(0).x + int(w / pow(2, i) / 2 * (1 + j * 2)) - node_r,
					point(0).y + node_r + i * node_r * 4}, node_r * 2, node_r * 2 });

				if (i > 0)
				{
					lines.add(Point{ nodes[nodes.size() - 1].point(0).x + node_r,
						nodes[nodes.size() - 1].point(0).y },
						Point{ nodes[nodes.size() - 1].point(0).x + node_r + int(w / pow(2, i) / 2) * (j % 2 == 0 ? 1 : -1),
						nodes[nodes.size() - 1].point(0).y - node_r * 2 });
				}
			}
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Graph" };

	Binary_tree_sq b_tree{ Point{200, 100}, 600, 600, 4 };
	b_tree.set_nodes();
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