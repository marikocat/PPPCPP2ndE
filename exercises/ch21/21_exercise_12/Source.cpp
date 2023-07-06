#include "Window.h"
#include "Graph.h"
#include "Gui.h"
#include "Order.h"

using namespace Graph_lib;

struct Querying_window : Window {
	Querying_window(Point xy, int w, int h, const string& title);
private:
	In_box filename;
	In_box name;
	Button quit_button;

	Out_box total_value;
	Button find_total_value_button;
	Button find_by_name_button;
	Button list_orders_button;

	void quit();
	void find_total();
	void find_by_name();
	void list_orders();
};

Querying_window::Querying_window(Point xy, int w, int h, const string& title)
	: Window{xy, w, h, title},
	filename{ Point{150, 0}, 150, 20, "File name: " },
	name{ Point{350, 0}, 150, 20, "Name: " },
	quit_button{Point{x_max() - 100, 0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Querying_window>(pw).quit(); } },
	total_value{Point{150, 50}, 100, 20, "Total value: "},
	find_total_value_button{Point{350, 50}, 150, 20, "Total value",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_total(); } },
	find_by_name_button{ Point{350, 100}, 150, 20, "Find orders by name",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_by_name(); } },
	list_orders_button{ Point{350, 150}, 150, 20, "List orders",
		[](Address, Address pw) {reference_to<Querying_window>(pw).list_orders(); } }
{
	attach(filename);
	attach(name);
	attach(total_value);
	attach(find_total_value_button);
	attach(find_by_name_button);
	attach(list_orders_button);
}

void Querying_window::quit()
{
	hide();
}

void Querying_window::find_total()
{
	string fn = filename.get_string();
	double tv = find_total_value(fn);
	total_value.put(tv);

	redraw();
}

void Querying_window::find_by_name()
{
	string fn = filename.get_string();
	string cn = name.get_string();

	vector<Order> orders;
	find_orders(fn, cn, orders);

	cout << "\nNumber of orders: " << orders.size() << "\n~~~~~\n";
	for (auto order : orders)
	{
		for (auto pur : order.vp) cout << pur;
		cout << '\n';
	}
	cout << "~~~~~\n";
}

void Querying_window::list_orders()
{
	string fn = filename.get_string();

	vector<Order> orders;
	get_orders_from_file(fn, orders);

	cout << "\nNumber of orders: " << orders.size() << "\n~~~~~\n";
	for (auto order : orders) cout << order;
	cout << "~~~~~\n";
}

int main()
try
{
	Querying_window win{ Point{100, 100}, 600, 400, "Query" };
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