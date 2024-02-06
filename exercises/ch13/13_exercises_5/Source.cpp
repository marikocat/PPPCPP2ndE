#include "Simple_window.h"
#include "Graph.h"

Point n(const Graph_lib::Circle& r);
Point s(const Graph_lib::Circle& r);
Point e(const Graph_lib::Circle& r);
Point w(const Graph_lib::Circle& r);
Point center(const Graph_lib::Circle& r);
Point ne(const Graph_lib::Circle& r);
Point se(const Graph_lib::Circle& r);
Point sw(const Graph_lib::Circle& r);
Point nw(const Graph_lib::Circle& r);

Point n(const Graph_lib::Ellipse& r);
Point s(const Graph_lib::Ellipse& r);
Point e(const Graph_lib::Ellipse& r);
Point w(const Graph_lib::Ellipse& r);
Point center(const Graph_lib::Ellipse& r);
Point ne(const Graph_lib::Ellipse& r);
Point se(const Graph_lib::Ellipse& r);
Point sw(const Graph_lib::Ellipse& r);
Point nw(const Graph_lib::Ellipse& r);

int main()
{
	Simple_window win{ Point{100, 100}, x_max() / 2, y_max() / 2, "Rect coordinates" };

	Graph_lib::Circle circ{ {win.x_max() / 4, win.y_max() / 4}, 100 };
	circ.set_color(Color::black);
	win.attach(circ);

	Mark m1{ n(circ), '1' };
	win.attach(m1);

	Mark m2{ s(circ), '2' };
	win.attach(m2);

	Mark m3{ e(circ), '3' };
	win.attach(m3);

	Mark m4{ w(circ), '4' };
	win.attach(m4);

	Mark m5{ center(circ), '5' };
	win.attach(m5);

	Mark m6{ ne(circ), '6' };
	win.attach(m6);

	Mark m7{ se(circ), '7' };
	win.attach(m7);

	Mark m8{ sw(circ), '8' };
	win.attach(m8);

	Mark m9{ nw(circ), '9' };
	win.attach(m9);

	win.wait_for_button();

	Graph_lib::Ellipse ellipse{ {win.x_max() * 3 / 4, win.y_max() / 4}, 100, 50 };
	ellipse.set_color(Color::black);
	win.attach(ellipse);

	Mark me1{ n(ellipse), '1' };
	win.attach(me1);

	Mark me2{ s(ellipse), '2' };
	win.attach(me2);

	Mark me3{ e(ellipse), '3' };
	win.attach(me3);

	Mark me4{ w(ellipse), '4' };
	win.attach(me4);

	Mark me5{ center(ellipse), '5' };
	win.attach(me5);

	Mark me6{ ne(ellipse), '6' };
	win.attach(me6);

	Mark me7{ se(ellipse), '7' };
	win.attach(me7);

	Mark me8{ sw(ellipse), '8' };
	win.attach(me8);

	Mark me9{ nw(ellipse), '9' };
	win.attach(me9);

	win.wait_for_button();
}

Point n(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius(), r.point(0).y };
}
Point s(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius(), r.point(0).y + r.radius() * 2 };
}
Point e(const Graph_lib::Circle& r)
{
	return { r.point(0).x, r.point(0).y + r.radius() };
}
Point w(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius() * 2, r.point(0).y + r.radius() };
}
Point center(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius(), r.point(0).y + r.radius() };
}
Point ne(const Graph_lib::Circle& r)
{
	return { r.point(0).x, r.point(0).y };
}
Point se(const Graph_lib::Circle& r)
{
	return { r.point(0).x, r.point(0).y + r.radius() * 2 };
}
Point sw(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius() * 2, r.point(0).y + r.radius() * 2 };
}
Point nw(const Graph_lib::Circle& r)
{
	return { r.point(0).x + r.radius() * 2, r.point(0).y };
}

Point n(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major(), r.point(0).y };
}
Point s(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major(), r.point(0).y + r.minor() * 2 };
}
Point e(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x, r.point(0).y + r.minor() };
}
Point w(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major() * 2, r.point(0).y + r.minor() };
}
Point center(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major(), r.point(0).y + r.minor() };
}
Point ne(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x, r.point(0).y };
}
Point se(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x, r.point(0).y + r.minor() * 2 };
}
Point sw(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major() * 2, r.point(0).y + r.minor() * 2 };
}
Point nw(const Graph_lib::Ellipse& r)
{
	return { r.point(0).x + r.major() * 2, r.point(0).y };
}