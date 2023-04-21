#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	struct Bar_data {
		int height, people_num;
	};

	istream& operator>>(istream& is, Bar_data& bd)
	{
		char ch1 = 0;
		char ch2 = 0;
		char ch3 = 0;
		Bar_data b_d;

		if (is >> ch1 >> b_d.height >> ch2 >> b_d.people_num >> ch3)
		{
			if (ch1 != '(' || ch2 != ',' || ch3 != ')')
			{
				is.clear(ios_base::failbit);
				return is;
			}
		}
		else return is;
		
		bd = b_d;
		return is;
	}

	class Bar : public Shape {
	public:
		Bar(Point tl, Point br, string value);

		void draw_lines() const override;
		void set_color(Color color);
		void set_fill_color(Color color);
	private:
		Rectangle r;
		Text t;
	};

	Bar::Bar(Point tl, Point br, string value)
		: r{ tl, br }, t{ {tl.x, br.y}, value }
	{
		t.move(40, 20);
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

	string value_to_string(int v)
	{
		ostringstream oss;
		oss << v;
		return oss.str();
	}

	class Bar_graph : public Shape {
	public:
		Bar_graph(Point origin, double wscale, double hscale, const vector<Bar_data>& values);

		void draw_lines() const override;
		void set_fill_color(Color color);
		void set_fill_color(int i, Color color);
		void set_color(Color color);
	private:
		Vector_ref<Bar> v;
	};

	Bar_graph::Bar_graph(Point origin, double wscale, double hscale, const vector<Bar_data>& values)
	{
		if (values.size() == 0) error("No data to graph");

		add(origin);

		for (int i = 0; i < values.size(); ++i)
		{
			v.push_back(new Bar{
				Point{point(0).x + int(i * wscale), point(0).y - int(hscale * values[i].people_num)},
				Point{point(0).x + int((i + 1) * wscale), point(0).y},
				value_to_string(values[i].height) });
			v[v.size() - 1].set_color(Color::black);
		}
	}

	void Bar_graph::draw_lines() const
	{
		for (int i = 0; i < v.size(); ++i)
			v[i].draw();
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
	}
}

int main()
try
{
	const int xmax = 800;
	const int ymax = 800;
	
	const int xoffset = 100;
	const int yoffset = 100;

	const int xspace = 50;   // space beyond axis
	const int yspace = 50;

	const int xlength = xmax - xoffset - xspace;    // length of axes
	const int ylength = ymax - yoffset - yspace;

	const int min_height = 170;
	const int max_height = 195;

	const double xscale = double(xlength - 50) / ((max_height - min_height) / 5 + 1);
	const double yscale = double(ylength) / 30;

	string file_name = "data.txt";
	ifstream ifs{ file_name };
	if (!ifs) error("can't open ", file_name);

	vector<Bar_data> vbd;
	for (Bar_data bd; ifs >> bd;)
		vbd.push_back(bd);

	Simple_window win{ Point{100, 100}, xmax, ymax, "Bar graph" };

	Axis x{ Axis::x, Point{xoffset, ymax - yoffset}, xlength, 0, "height, cm" };
	x.label.move(xlength - 150, 0);
	x.set_color(Color::red);
	Axis y{ Axis::y, Point{xoffset, ymax - yoffset}, ylength, int(ylength / yscale / 10), "number of people" };
	y.label.move(0, -5);
	y.set_color(Color::red);

	Vector_ref<Text> num_labels;
	for (int i = 0; i < 4; ++i)
	{
		num_labels.push_back(new Text{ {xoffset - 20, ymax - yoffset + 5 - int(i * 10 * yscale)}, value_to_string(i * 10) });
		num_labels[num_labels.size() - 1].set_color(Color::red);
		win.attach(num_labels[num_labels.size() - 1]);
	}

	Bar_graph bar_graph{ Point{xoffset, ymax - yoffset}, xscale, yscale, vbd };
	
	win.attach(x);
	win.attach(y);
	win.attach(bar_graph);
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