#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Bar : public Shape {
	public:
		Bar(Point orig, int width, int height, string value);

		void draw_lines() const override;
		void set_color(Color color);
		void set_fill_color(Color color);
	private:
		Rectangle r;
		Text t;
	};

	Bar::Bar(Point tl, int width, int height, string value)
		: r{ tl, width, height }, t{ tl, value }
	{
		t.move(0, -5);
	}

	void Bar::draw_lines() const
	{
		r.draw();
		t.draw();
	}

	void Bar::set_color(Color color)
	{
		r.set_color(color);
		t.set_color(color);
	}

	void Bar::set_fill_color(Color color)
	{
		r.set_fill_color(color);
	}

	string value_to_string(double v)
	{
		ostringstream oss;
		oss << v;
		return oss.str();
	}

	class Bar_graph : public Shape {
	public:
		Bar_graph(Point origin, int width, int height, const vector<double>& values, string label);

		void draw_lines() const override;
		void set_fill_color(Color color);
		void set_fill_color(int i, Color color);
		void set_color(Color color);
	private:
		int w;
		int h;
		Vector_ref<Bar> v;
		Text l;
	};

	Bar_graph::Bar_graph(Point origin, int width, int height, const vector<double>& values, string label)
		: w{ width }, h{ height }, l{{origin.x, origin.y + 20}, label}
	{
		if (values.size() == 0) error("No data to graph");

		add(origin);

		int wscale;
		int hscale;
		double max_v = 0;
		for (int i = 0; i < values.size(); ++i)
		{
			if (values[i] < 0) error("Value less then 0");
			if (max_v < values[i]) max_v = values[i];
		}
		hscale = height / max_v;
		wscale = width / values.size();

		for (int i = 0; i < values.size(); ++i)
		{
			v.push_back(new Bar{
				Point{point(0).x + i * wscale, point(0).y - int(hscale * values[i])},
				wscale, 
				int(hscale * values[i]), 
				value_to_string(values[i])});
			v[v.size() - 1].set_color(Color::black);
		}
		l.set_color(Color::black);
	}

	void Bar_graph::draw_lines() const
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].draw();
		l.draw();
	}

	void Bar_graph::set_fill_color(Color color)
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].set_fill_color(color);
	}

	void Bar_graph::set_fill_color(int i, Color color)
	{
		v[i].set_fill_color(color);
	}

	void Bar_graph::set_color(Color color)
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].set_color(color);
		l.set_color(color);
	}
}

int main()
try
{
	Simple_window win{ Point{100, 100}, 800, 800, "Bar graph" };

	vector<double> vd{ 1.5, 15.3, 18.9, 29.0, 50, 35.9, 18.3, 38.9, 12, 18.2, 46.5 };
	Bar_graph bg{ Point{150, 600}, 500, 300, vd, "Bar graph"};
	bg.set_fill_color(Color::green);
	bg.set_fill_color(3, Color::magenta);
	bg.set_color(Color::dark_blue);

	win.attach(bg);
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