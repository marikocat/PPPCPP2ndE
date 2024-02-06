#include "Simple_window.h"
#include "Graph.h"

class DailyTemp {
	int temp;
public:
	DailyTemp() { temp = 0; }
	DailyTemp(int x) { temp = x; }
	DailyTemp& operator=(int x) {
		temp = x; return *this;
	}
	double get_temp() { return temp; }
};

int main()
try
{
	using namespace Graph_lib;

	Simple_window win(Point{ 100, 100 }, 800, 1000, "My window");

	Lines grid;
	for (int i = 0; i <= 8; ++i)
		grid.add(Point{ i * 100, 0 }, Point{ i * 100, 800 });
	for (int i = 0; i <= 8; ++i)
		grid.add(Point{ 0, i * 100 }, Point{ win.x_max(), i * 100 });
	grid.set_color(Color::black);

	win.attach(grid);

	win.wait_for_button();

	Vector_ref<Graph_lib::Rectangle> rects;
	for (int i = 0; i < 8; ++i)
	{
		rects.push_back(new Graph_lib::Rectangle{ Point{i * 100, i * 100}, 100, 100 });
		rects[rects.size() - 1].set_fill_color(Color::red);
		rects[rects.size() - 1].set_color(Color::invisible);
		win.attach(rects[rects.size() - 1]);
	}

	win.wait_for_button();

	Image img1{ Point{0, 400}, "coffee.jpg" };
	Image img2{ Point{200, 600}, "coffee.jpg" };
	Image img3{ Point{500, 100}, "coffee.jpg" };
	win.attach(img1);
	win.attach(img2);
	win.attach(img3);

	win.wait_for_button();

	Image img4(Point{ 0, 0 }, "image.jpg");
	win.attach(img4);

	for (int i = 1; i < 4; ++i)
	{
		img4.move(0, 100);
		win.wait_for_button();
	}

	vector<DailyTemp> vr;
	for (int i = 0; i < 7; i++)
		vr.push_back(DailyTemp(60 + rand() % 30));
	cout << "Fahrenheit temperatures:\n";
	for (int i = 0; i < vr.size(); i++)
		cout << vr[i].get_temp() << " ";
	cout << endl;
}
catch (exception& e)
{
	return 1;
}
catch (...)
{
	return 2;
}