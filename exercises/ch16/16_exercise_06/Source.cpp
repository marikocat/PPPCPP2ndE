#include "Gui.h"
#include <thread>
#include <chrono>

const double pi = atan(1) * 4;

using namespace Graph_lib;

struct Hand : Shape {
	Hand(Point p1, Point p2) { add(p1); add(p2); }
	void set_end_point(Point xy);
};

void Hand::set_end_point(Point xy)
{
	set_point(1, xy);
}

class Clock : public Circle {
public:
	Clock(Point center, int radius);

	void draw_lines() const override;
	void set_color(Color color);

	void move_hour_hand(int i = 1);
	void move_minute_hand(int i = 1);
	void move_second_hand(int i = 1);
private:
	int hour;
	int minute;
	int second;
	Hand hour_hand;
	Hand minute_hand;
	Hand second_hand;
};

Clock::Clock(Point center, int radius)
	: Circle{ center, radius },
	hour_hand{center, {center.x, center.y - radius / 2}},
	minute_hand{center, {center.x, center.y - radius / 4}},
	second_hand{center, {center.x, center.y - radius}}
{
	set_color(Color::black);

	time_t raw_time;
	time(&raw_time);
	tm local_time;
	localtime_s(&local_time, &raw_time);

	hour = local_time.tm_hour;
	minute = local_time.tm_min;
	second = local_time.tm_sec;

	move_hour_hand(0);
	move_minute_hand(0);
	move_second_hand(0);
}

void Clock::draw_lines() const
{
	Circle::draw_lines();

	hour_hand.draw();
	minute_hand.draw();
	second_hand.draw();
}

void Clock::set_color(Color color)
{
	Circle::set_color(color);

	hour_hand.set_color(color);
	minute_hand.set_color(color);
	second_hand.set_color(color);
}

void Clock::move_hour_hand(int i)
{
	const int hours_num = 12;
	hour = (hour + i) % hours_num;
	int x1 = center().x + int(radius() / 2 * cos((hours_num / 4 - hour) * 360 / hours_num * pi / 180));
	int y1 = center().y - int(radius() / 2 * sin((hours_num / 4 - hour) * 360 / hours_num * pi / 180));
	hour_hand.set_end_point(Point{ x1, y1 });
}

void Clock::move_minute_hand(int i)
{
	const int minutes_num = 60;
	if (minute + i >= minutes_num)
	{
		move_hour_hand((minute + i) / minutes_num);
	}
	minute = (minute + i) % minutes_num;
	int x1 = center().x + int(radius() * 3 / 4 * cos((minutes_num / 4 - minute) * 360 / minutes_num * pi / 180));
	int y1 = center().y - int(radius() * 3 / 4 * sin((minutes_num / 4 - minute) * 360 / minutes_num * pi / 180));
	minute_hand.set_end_point(Point{ x1, y1 });
}
void Clock::move_second_hand(int i)
{
	const int seconds_num = 60;
	if (second + i >= seconds_num)
	{
		move_minute_hand((second + i) / seconds_num);
	}
	second = (second + i) % seconds_num;
	int x1 = center().x + int(radius() * cos((seconds_num / 4 - second) * 360 / seconds_num * pi / 180));
	int y1 = center().y - int(radius() * sin((seconds_num / 4 - second) * 360 / seconds_num * pi / 180));
	second_hand.set_end_point(Point{ x1, y1 });
}

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	Clock clock;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	clock{Point{w / 2, h / 2}, 100}
{
	attach(next_button);
	attach(quit_button);
	attach(clock);
}

void My_window::wait_for_button()
{
	while (!next_button_pushed && !quit_button_pushed)
	{
		Fl::wait();
		this_thread::sleep_for(chrono::seconds(1));
		clock.move_second_hand();
		redraw();
	}
	if (next_button_pushed)
	{
		next_button_pushed = false;
		Fl::redraw();
	}
}

void My_window::cb_next(Address, Address pw)
{
	reference_to<My_window>(pw).next();
}

void My_window::cb_quit(Address, Address pw)
{
	reference_to<My_window>(pw).quit();
}

void My_window::next()
{
	next_button_pushed = true;
}

void My_window::quit()
{
	quit_button_pushed = true;
	hide();
}

int main()
try
{
	My_window win{ Point{100, 100}, 600, 400, "My window" };
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