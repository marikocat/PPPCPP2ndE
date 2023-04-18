#include "Simple_window.h"
#include "Graph.h"

namespace Graph_lib {
	class Controller {
		virtual void on() = 0;
		virtual void off() = 0;
		virtual void set_level(int l) = 0;
		virtual void show() = 0;
	};

	class Controller1 : public Controller {
	public:
		void on() { is_on = true; }
		void off() { is_on = false; }
		void set_level(int l) { level = l; }
		void show();
	private:
		bool is_on{ false };
		int level{ 0 };
	};

	void Controller1::show()
	{
		cout << (is_on ? "On\n" : "Off\n");
		cout << "Level is " << level << "\n";
	}

	class Controller2 : public Controller {
	public:
		Controller2(Shape& sh) : shape{ sh } {}
		void on();
		void off();
		void set_level(int l);
		void show();
	private:
		Shape& shape;
		bool is_visible{ true };
	};

	void Controller2::on()
	{
		is_visible = true;
		shape.set_color(Color::visible);
	}
	void Controller2::off()
	{
		is_visible = false;
		shape.set_color(Color::invisible);
	}

	void Controller2::set_level(int l)
	{
		shape.set_color(l);
	}

	void Controller2::show()
	{
		cout << (is_visible ? "Visible\n" : "Invisible\n");
		cout << "Color is " << shape.color().as_int() << "\n";
	}

	class Controller3 : public Controller {
	public:
		Controller3(Shape& sh) : shape{ sh } {}
		void on();
		void off();
		void set_level(int l);
		void show();
	private:
		Shape& shape;
		bool is_solid{ true };
	};

	void Controller3::on()
	{
		is_solid = true;
		shape.set_style(Line_style::solid);
	}

	void Controller3::off()
	{
		is_solid = false;
		shape.set_style(Line_style::dash);
	}

	void Controller3::set_level(int l)
	{
		if (is_solid)
			shape.set_style(Line_style{ Line_style::solid, l });
		else
			shape.set_style(Line_style{ Line_style::dash, l });
	}

	void Controller3::show()
	{
		cout << (is_solid ? "Solid\n" : "Dashed\n");
		cout << "Line width is " << shape.style().width() << "\n";
	}
}

int main()
try
{
	using namespace Graph_lib;

	Simple_window win{ Point{100, 100}, 1280, 720, "Controller" };

	Controller1 c1;
	c1.on();
	c1.set_level(10);
	c1.show();

	Graph_lib::Rectangle rect{ {150, 150}, 150, 150 };
	Controller2 c2{ rect };
	c2.on();
	c2.set_level(150);

	Circle circ{ {500, 300}, 150 };
	Controller2 cc2{ circ };
	Controller3 c3{ circ };
	c3.off();
	c3.set_level(3);
	cc2.set_level(120);

	win.attach(rect);
	win.attach(circ);
	win.wait_for_button();

	c2.off();
	cc2.set_level(110);
	c3.on();
	c3.set_level(5);
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