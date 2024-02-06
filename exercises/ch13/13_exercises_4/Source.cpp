#include "Simple_window.h"
#include "Graph.h"

Point n(const Graph_lib::Rectangle& r);
Point s(const Graph_lib::Rectangle& r);
Point e(const Graph_lib::Rectangle& r);
Point w(const Graph_lib::Rectangle& r);
Point center(const Graph_lib::Rectangle& r);
Point ne(const Graph_lib::Rectangle& r);
Point se(const Graph_lib::Rectangle& r);
Point sw(const Graph_lib::Rectangle& r);
Point nw(const Graph_lib::Rectangle& r);

int main()
{
	Simple_window win{ Point{100, 100}, x_max() / 2, y_max() / 2, "Rect coordinates" };

	Graph_lib::Rectangle rect{ {win.x_max() / 4, win.y_max() / 4}, {win.x_max() / 2, win.y_max() / 2} };
	rect.set_color(Color::black);
	win.attach(rect);

	Mark m1{ n(rect), '1' };
	win.attach(m1);

	Mark m2{ s(rect), '2' };
	win.attach(m2);

	Mark m3{ e(rect), '3' };
	win.attach(m3);

	Mark m4{ w(rect), '4' };
	win.attach(m4);

	Mark m5{ center(rect), '5' };
	win.attach(m5);

	Mark m6{ ne(rect), '6' };
	win.attach(m6);

	Mark m7{ se(rect), '7' };
	win.attach(m7);

	Mark m8{ sw(rect), '8' };
	win.attach(m8);

	Mark m9{ nw(rect), '9' };
	win.attach(m9);

	win.wait_for_button();
}

Point n(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y };
}
Point s(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y + r.height()};
}
Point e(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x, r.point(0).y + r.height() / 2 };
}
Point w(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y + r.height() / 2 };
}
Point center(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width() / 2, r.point(0).y + r.height() / 2 };
}
Point ne(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x, r.point(0).y };
}
Point se(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x, r.point(0).y + r.height() };
}
Point sw(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y + r.height() };
}
Point nw(const Graph_lib::Rectangle& r)
{
	return { r.point(0).x + r.width(), r.point(0).y };
}