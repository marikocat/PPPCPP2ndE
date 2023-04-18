#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Binary_tree : public Shape {
	public:
		Binary_tree(Point tl, int win_width, int win_height, int levels);

		void draw_lines() const override;

		void move(int dx, int dy);
		void set_color(Color color);
		void set_node_label(int level, int num, const string& label);

		int width() const { return w; }
		int height() const { return h; }
		int levels_num() const { return l; }
	private:
		int w;
		int h;
		int l;
		int node_r;
		Vector_ref<Circle> nodes;
		Lines lines;
		Vector_ref<Text> labels;
	};

	Binary_tree::Binary_tree(Point tl, int win_width, int win_height, int levels)
		: w{ win_width }, h{ win_height }, l{ levels }
	{
		if (levels < 0) error("Invalid number of levels");

		add(tl);

		int node_width = win_width / pow(2, levels);
		int node_height = win_height / levels / 2;
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

		for (int i = 0; i < labels.size(); ++i)
			labels[i].draw();
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

		for (int i = 0; i < labels.size(); ++i)
			labels[i].set_color(color);
	}

	void Binary_tree::set_node_label(int level, int col, const string& label)
	{
		int num = 0;
		if (level > 1)
		{
			for (int i = 0; i < level - 1; ++i)
			{
				num += pow(2, i);
			}
			num += (col - 1);
			cout << "num = " << num << "\n";
		}
		labels.push_back(new Text{ Point{nodes[num].point(0).x + node_r / 3 * 2, nodes[num].point(0).y + node_r / 3 * 4 }, label });
		labels[labels.size() - 1].set_font_size(node_r);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 600, 600, "Graph" };

	Binary_tree b_tree{ Point{0, 0}, 600, 600, 4 };
	b_tree.set_node_label(3, 2, "2");
	b_tree.set_node_label(3, 4, "4");
	b_tree.set_node_label(4, 5, "5");
	b_tree.set_node_label(1, 1, "1");

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