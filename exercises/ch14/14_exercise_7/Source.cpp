#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Striped_closed_polyline : public Closed_polyline {
	public:
		using Closed_polyline::Closed_polyline;

		void draw_lines() const override;
	};

	inline pair<double, double> line_intersect(Point p1, Point p2, Point p3, Point p4, bool& parallel);

	bool line_segment_intersect(Point p1, Point p2, Point p3, Point p4, Point& intersection);

	void Striped_closed_polyline::draw_lines() const
	{
		int min_x = point(0).x;
		int max_x = min_x;
		int min_y = point(0).y;
		int max_y = min_y;
		for (int i = 0; i < number_of_points(); ++i)
		{
			if (point(i).x < min_x) min_x = point(i).x;
			if (point(i).x > max_x) max_x = point(i).x;
			if (point(i).y < min_y) min_y = point(i).y;
			if (point(i).y > max_y) max_y = point(i).y;
		}
		if (fill_color().visibility()) {
			fl_color(fill_color().as_int());
			for (int i = 1; i < max_y - min_y; i += 4)
			{
				vector<int> in_xs;
				Point intersection{ 0, min_y + i };
				for (int j = 0; j < number_of_points(); ++j)
				{
					if (Graph_lib::line_segment_intersect(Point{ min_x, min_y + i }, Point{ max_x, min_y + i },
						point(j), point((j + 1) % number_of_points()), intersection))
					{
						cout << "point " << j << " and point " << (j + 1) % number_of_points() << "\n";
						in_xs.push_back(intersection.x);
					}
				}
				sort(in_xs.begin(), in_xs.end());
				cout << "size of in_xs: " << in_xs.size() << "\n";
				for (int k = 0; k < in_xs.size(); k += 2)
				{
					fl_line(in_xs[k], min_y + i, in_xs[k + 1], min_y + i);
				}
			}
			fl_color(color().as_int());	// reset color
		}

		if (color().visibility())
			Shape::draw_lines();

		if (color().visibility())	// draw closing line:
			fl_line(point(number_of_points() - 1).x, point(number_of_points() - 1).y, point(0).x, point(0).y);
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, {"Striped closed polyline"} };

	Striped_closed_polyline s_cl_polyline;
	s_cl_polyline.add(Point{ 100, 100 });
	s_cl_polyline.add(Point{ 350, 350 });
	s_cl_polyline.add(Point{ 400, 200 });
	s_cl_polyline.add(Point{ 150, 300 });
	s_cl_polyline.set_color(Color::black);
	s_cl_polyline.set_fill_color(Color::dark_blue);

	win.attach(s_cl_polyline);
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