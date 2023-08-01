#include "Simple_window.h"
using namespace Graph_lib;

istream& operator>>(istream& is, Point& p)
{
	string s;
	char ch;
	while (is >> ch)
	{
		if (ch == '(')
			break;
		s += ch;
	}
	if (s != "Point")
		throw exception("bad input: not a Point()");

	char ch1, ch2;
	int x, y;
	if (is >> x >> ch1 >> y >> ch2 && (ch1 != ',' || ch2 != ')'))
		throw exception("bad input: not coordinates for a Point()");
	p = Point(x, y);
	return is;
}

Circle* get_circle(istream& is)
{
	char ch1, ch2, ch3;
	Point p;
	int r;
	if (is >> ch1 >> p >> ch2 >> r >> ch3 && (ch1 != '(' || ch2 != ',' || ch3 != ')'))
		throw exception("bad input: not a Circle()");
	return new Circle(p, r);
}

Graph_lib::Rectangle* get_rectangle(istream& is)
{
	char ch1, ch2, ch3;
	Point p1, p2;
	if (is >> ch1 >> p1 >> ch2 >> p2 >> ch3 && (ch1 != '(' || ch2 != ',' || ch3 != ')'))
		throw exception("bad input: not a Rectangle()");
	return new Graph_lib::Rectangle(p1, p2);
}

Line* get_line(istream& is)
{
	char ch1, ch2, ch3;
	Point p1, p2;
	if (is >> ch1 >> p1 >> ch2 >> p2 >> ch3 && (ch1 != '(' || ch2 != ',' || ch3 != ')'))
		throw exception("bad input: not a Line()");
	return new Line(p1, p2);
}

Shape* get_shape(istream& is)
{
	string shape_type;
	char ch;
	while (is >> ch)
	{
		if (ch == '(')
		{
			is.unget();
			break;
		}
		shape_type += ch;
	}
	if (shape_type == "Circle")
	{
		return get_circle(is);
	}
	else if (shape_type == "Rectangle")
	{
		return get_rectangle(is);
	}
	else if (shape_type == "Line")
	{
		return get_line(is);
	}
	else
	{
		while (is.get(ch))
		{
			if (is.eof() || ch == '\n')
				break;
		}
		return 0;
	}
}

int main()
try
{
	Simple_window s_win{ Point(100, 100), 1200, 800, "My window" };

	ifstream ifs{ "in.txt" };
	if (!ifs)
		throw exception("cannot open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	Vector_ref<Shape> vs;
	while (Shape* s = get_shape(ifs))
	{
		vs.push_back(s);
		s_win.attach(vs[vs.size() - 1]);
		vs[vs.size() - 1].set_color(Color::black);
	}
	s_win.wait_for_button();
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	exit(1);
}
catch (...)
{
	cerr << "unknown error\n";
	exit(2);
}