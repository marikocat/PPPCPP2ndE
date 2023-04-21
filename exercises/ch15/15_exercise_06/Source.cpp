#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Bar_graph : public Shape {
	public:
		Bar_graph(Point origin, int width, int height, const vector<double>& values);

		void draw_lines() const override;
	private:
		int w;
		int h;
		Vector_ref<Rectangle> v;
	};

	Bar_graph::Bar_graph(Point origin, int width, int height, const vector<double>& values)
		: w{width}, h{height}
	{
		if (values.size() == 0) error("No data to graph");

		add(origin);

		double wscale;
		double hscale;
		double max_v = 0;
		for (int i = 0; i < values.size(); ++i)
		{
			if (values[i] < 0) error("Value less then 0");
			if (max_v < values[i]) max_v = values[i];
		}
		hscale = height / max_v;
		wscale = (double) width / values.size();

		for (int i = 0; i < values.size(); ++i)
		{
			v.push_back(new Rectangle{
				{int(point(0).x + i * wscale), int(point(0).y - hscale * values[i])},
				{int(point(0).x + i * wscale + wscale), point(0).y} });
			v[v.size() - 1].set_color(Color::black);
		}
	}

	void Bar_graph::draw_lines() const
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].draw();
	}
}

int main()
try
{
	Simple_window win{ Point{100, 100}, 800, 800, "Bar graph" };

	vector<double> vd{ 1.5, 15.3, 18.9, 29.0, 50, 35.9, 18.3, 38.9, 12, 18.2, 46.5 };
	Bar_graph bg{ Point{150, 600}, 500, 300, vd };

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