#include "Simple_window.h"
#include "Graph.h"

const double pi = atan(1) * 4;

namespace Graph_lib {
	struct Arrow : Shape {
		Arrow(Point start, Point end, double head_angle, int head_size)
			: ha{ head_angle }, hs{ head_size }
		{
			add(start);
			add(end);
		}

		void draw_lines() const;
	private:
		double ha;
		int hs;
	};

	void Arrow::draw_lines() const
	{
		fl_line(point(0).x, point(0).y, point(1).x, point(1).y);

		double line_angle = atan2(point(1).y - point(0).y, point(1).x - point(0).x);

		fl_line(point(1).x,
			point(1).y,
			int(point(1).x - hs * cos(line_angle + ha)),
			int(point(1).y - hs * sin(line_angle + ha)));
		fl_line(point(1).x,
			point(1).y,
			int(point(1).x - hs * cos(line_angle - ha)),
			int(point(1).y - hs * sin(line_angle - ha)));
	}

	class Class_hierarchy : public Shape {
	public:
		Class_hierarchy(Point tl, int levels, int win_width, int level_max_nodes_num);

		void draw_lines() const override;

		void add_nodes(int orig_level, int orig_col, int nodes_num);
		void set_node_label(int level, int col, const string& label);

		void set_color(Color color);

		int width() const { return w; }
		int levels_num() const { return l; }
	private:
		int w;
		int l;
		int node_r;
		Vector_ref<Vector_ref<Circle>> nodes;
		Vector_ref<Vector_ref<Arrow>> arrows;
		Vector_ref<Vector_ref<Text>> labels;
	};

	Class_hierarchy::Class_hierarchy(Point tl, int levels, int win_width, int level_max_nodes_num)
		: w{ win_width }, l{ levels }
	{
		if (levels < 0) error("Invalid number of levels");

		add(tl);

		for (int i = 0; i < levels; ++i)
		{
			nodes.push_back(new Vector_ref<Circle>{});
			arrows.push_back(new Vector_ref<Arrow>{});
			labels.push_back(new Vector_ref<Text>{});
		}

		node_r = win_width / level_max_nodes_num / 4;
		if (levels > 0)
			nodes[0].push_back(new Circle{ {point(0).x + win_width / 2, point(0).y + node_r * 2}, node_r });
	}

	void Class_hierarchy::add_nodes(int orig_level, int orig_col, int nodes_num)
	{
		double head_angle = 10 * pi / 180;
		int head_size = 20;

		int orig_x = nodes[orig_level - 1][orig_col - 1].center().x;
		int orig_y = nodes[orig_level - 1][orig_col - 1].center().y;

		int level_nodes_num = nodes[orig_level].size();

		for (int i = level_nodes_num; i < level_nodes_num + nodes_num; ++i)
		{
			nodes[orig_level].push_back(new Circle{
				{point(0).x + node_r * (1 + i * 4),
				point(0).y + orig_y + node_r * 4}, 
				node_r });

			arrows[orig_level].push_back(new Arrow{
					{ nodes[orig_level][i].center().x, nodes[orig_level][i].center().y - node_r },
					{ orig_x, orig_y + node_r }, head_angle, head_size });
			arrows[orig_level][i].set_color(Color::black);
		}
	}

	void Class_hierarchy::set_node_label(int level, int col, const string& label)
	{
		int font_size = node_r / 4;
		labels[level - 1].push_back(new Text{
			{int(nodes[level - 1][col - 1].center().x - label.size() / 2 * font_size / 2), 
			nodes[level - 1][col - 1].center().y}, 
			label });
		labels[level - 1][labels[level - 1].size() - 1].set_font_size(font_size);
		labels[level - 1][labels[level - 1].size() - 1].set_color(Color::black);
	}

	void Class_hierarchy::draw_lines() const
	{
		for (int i = 0; i < nodes.size(); ++i)
			for (int j = 0; j < nodes[i].size(); ++j)
			nodes[i][j].draw();

		for (int i = 0; i < arrows.size(); ++i)
			for (int j = 0; j < arrows[i].size(); ++j)
			arrows[i][j].draw();

		for (int i = 0; i < labels.size(); ++i)
			for (int j = 0; j < labels[i].size(); ++j)
				labels[i][j].draw();
	}

	void Class_hierarchy::set_color(Color color)
	{
		Shape::set_color(color);

		for (int i = 0; i < nodes.size(); ++i)
			for (int j = 0; j < nodes[i].size(); ++j)
			nodes[i][j].set_color(color);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ {100, 100}, 1280, 720, "Class hierarchy" };

	Class_hierarchy ch{ {0, 0}, 3, 1200, 6 };
	ch.add_nodes(1, 1, 6);
	ch.add_nodes(2, 1, 2);
	ch.add_nodes(2, 6, 3);

	ch.set_node_label(1, 1, "exception");
	ch.set_node_label(2, 1, "runtime_error");
	ch.set_node_label(2, 2, "bad_alloc");
	ch.set_node_label(2, 3, "bad_cast");
	ch.set_node_label(2, 4, "bad_type_id");
	ch.set_node_label(2, 5, "bad_exception");
	ch.set_node_label(2, 6, "logic_error");
	ch.set_node_label(3, 1, "overflow_error");
	ch.set_node_label(3, 2, "underflow_error");
	ch.set_node_label(3, 3, "invalid_argument");
	ch.set_node_label(3, 4, "length_error");
	ch.set_node_label(3, 5, "out_of_range");
	ch.set_color(Color::black);

	win.attach(ch);
	win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	return 2;
}