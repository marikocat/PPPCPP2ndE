#include "Gui.h"

using namespace Graph_lib;

struct Currency {
	enum Code {
		USD, EUR, GBP, JPY
	};
	string name;
	double rate;
};

istream& operator>>(istream& is, Currency& currency)
{
	char ch1;
	char ch2;
	string n;
	double r;

	is >> ch1 >> n >> r >> ch2;
	if (!is) return is;
	if (ch1 != '(' || ch2 != ')')
	{
		is.clear(ios_base::failbit);
		return is;
	}

	currency.name = n;
	currency.rate = r;
	return is;
}

struct My_window : Window {
	My_window(Point xy, int w, int h, const string& title);

	void wait_for_button();
private:
	Button next_button;
	bool next_button_pushed;

	Button quit_button;
	bool quit_button_pushed;

	vector<Currency> currencies;
	Currency::Code from_code = Currency::USD;
	Currency::Code to_code = Currency::USD;

	In_box in_c;
	Out_box out_c;
	Button convert_button;
	Menu from_menu;
	Menu to_menu;

	static void cb_next(Address, Address);
	void next();

	static void cb_quit(Address, Address);
	void quit();

	void convert();
	void set_from_code(Currency::Code cc) { from_code = cc; }
	void set_to_code(Currency::Code cc) { to_code = cc; }
};

My_window::My_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next", cb_next },
	next_button_pushed{ false },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit", cb_quit },
	quit_button_pushed{ false },
	in_c{Point{100, 100}, 70, 20, "From: "},
	out_c{Point{300, 100}, 70, 20, "To: "},
	convert_button{Point{500, 100}, 70, 20, "Convert",
		[](Address, Address pw) {reference_to<My_window>(pw).convert(); } },
	from_menu{Point{100, 140}, 70, 20, Menu::vertical, "From currency"},
	to_menu{Point{300, 140}, 70, 20, Menu::vertical, "To currency"}
{
	attach(next_button);
	attach(quit_button);
	attach(in_c);
	attach(out_c);
	attach(convert_button);

	const string file_name{ "conversion_rates.txt" };
	ifstream ifs{ file_name };
	if (!ifs) error("cannot open ", file_name);

	for (Currency c; ifs >> c;)
		currencies.push_back(c);

	from_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::USD].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_from_code(Currency::USD); } });
	from_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::EUR].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_from_code(Currency::EUR); } });
	from_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::GBP].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_from_code(Currency::GBP); } });
	from_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::JPY].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_from_code(Currency::JPY); } });
	to_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::USD].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_to_code(Currency::USD); } });
	to_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::EUR].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_to_code(Currency::EUR); } });
	to_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::GBP].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_to_code(Currency::GBP); } });
	to_menu.attach(new Button{ Point{0, 0}, 0, 0, currencies[Currency::JPY].name,
		[](Address, Address pw) {reference_to<My_window>(pw).set_to_code(Currency::JPY); } });
	attach(from_menu);
	attach(to_menu);
}

void My_window::wait_for_button()
{
	while (!next_button_pushed && !quit_button_pushed)
	{
		Fl::wait();
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

void My_window::convert()
{
	istringstream iss{in_c.get_string()};
	double from_amount;
	iss >> from_amount;

	double from_amount_usd = from_amount / currencies[from_code].rate;
	double to_amount = from_amount_usd * currencies[to_code].rate;

	ostringstream oss;
	oss << fixed << setprecision(2) << to_amount;
	out_c.put(oss.str());
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