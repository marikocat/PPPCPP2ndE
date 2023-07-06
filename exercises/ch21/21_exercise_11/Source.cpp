#include "Window.h"
#include "Graph.h"
#include "Gui.h"
#include "Order.h"

using namespace Graph_lib;

struct Orders_window : Window {
	Orders_window(Point xy, int w, int h, const string& title);
private:
	In_box name;
	In_box address;
	Button next_button;
	Button quit_button;

	In_box unit_name;
	In_box unit_price;
	In_box count;
	Button next_purchase_button;

	Out_box orders_count;

	vector<Purchase> vp;
	int orders_num = 0;

	void next();
	void quit();
	void next_purchase();
};

Orders_window::Orders_window(Point xy, int w, int h, const string& title)
	: Window{ xy, w, h, title },
	name{ Point{50, 0}, 150, 20, "Name: " },
	address{ Point{300, 0}, 150, 20, "Address: " },
	next_button{ Point{x_max() - 150, 0}, 70, 20, "Next",
		[](Address, Address pw) {reference_to<Orders_window>(pw).next(); } },
	quit_button{Point{x_max() - 70, 0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Orders_window>(pw).quit(); } },
	unit_name{Point{150, 70}, 100, 20, "Unit name: "},
	unit_price{Point{150, 105}, 100, 20, "Unit_price: "},
	count{ Point{350, 105}, 100, 20, "Count: " },
	next_purchase_button{ Point{150, 140}, 150, 20, "Next purchase",
		[](Address, Address pw) {reference_to<Orders_window>(pw).next_purchase(); } },
	orders_count{Point{300, 300}, 150, 20, "Orders written to a file: "}
{
	attach(name);
	attach(address);
	attach(next_button);
	attach(quit_button);
	attach(unit_name);
	attach(unit_price);
	attach(count);
	attach(next_purchase_button);
	attach(orders_count);
}

void Orders_window::quit()
{
	hide();
}

void Orders_window::next_purchase()
{
	string n = unit_name.get_string();
	string sp = unit_price.get_string();
	double p = stod(sp);
	int c = count.get_int();

	Purchase pp{ n, p, c };
	vp.push_back(pp);

	for (auto pur : vp) cout << pur << '\n';
}

void Orders_window::next()
{
	string n = name.get_string();
	string a = address.get_string();

	Order o{ n, a, vp };
	ofstream ofs{ "out.txt", ios_base::app };
	if (!ofs) throw exception("could not open file");
	ofs.exceptions(ofs.exceptions() | ios_base::badbit);

	ofs << o;
	orders_num++;
	orders_count.put(orders_num);

	vp.clear();

	redraw();
}

int main()
try
{
	Orders_window win{ Point{100, 100}, 600, 400, "Orders" };
	return gui_main();
}
catch (exception& e)
{
	cerr << "exception: " << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Some exception\n";
	return 2;
}