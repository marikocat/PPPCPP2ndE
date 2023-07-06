#include "Window.h"
#include "Graph.h"
#include "Gui.h"
#include "Query.h"

using namespace Graph_lib;

struct Querying_window : Window {
	Querying_window(Point xy, int w, int h, const string& title);
private:
	In_box filename;
	Button set_filename_b;
	Button quit_b;
	In_box input;
	Button find_occurence_frequency_b;
	Button find_most_frequent_b;
	Button find_longest_b;
	Button find_shortest_b;
	Button list_words_b;
	Button list_length_words_b;

	Multiline_out_box result;

	map<string, int> msi;

	void quit();
	void set_filename();
	void find_occurence_frequency();
	void find_most_frequent();
	void find_longest();
	void find_shortest();
	void list_words();
	void list_length_words();
};

Querying_window::Querying_window(Point xy, int w, int h, const string& title)
	: Window{xy, w, h, title},
	filename{ Point{100, 0}, 100, 20, "File name: " },
	set_filename_b{Point{250, 0}, 100, 20, "Set file name",
		[](Address, Address pw) {reference_to<Querying_window>(pw).set_filename(); } },
	quit_b{Point{x_max() - 70, 0}, 70, 20, "Quit",
		[](Address, Address pw) {reference_to<Querying_window>(pw).quit(); } },
	input{ Point{100, 50}, 100, 20, "Input: " },
	find_occurence_frequency_b{ Point{50, 100}, 250, 20, "Find occurence of the input frequency",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_occurence_frequency(); } },
	find_most_frequent_b{ Point{50, 150}, 250, 20, "Find most frequent word",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_most_frequent(); } },
	find_longest_b{ Point{50, 200}, 200, 20, "Find the longest word",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_longest(); } },
	find_shortest_b{ Point{300, 200}, 200, 20, "Find the shortest word",
		[](Address, Address pw) {reference_to<Querying_window>(pw).find_shortest(); } },
	list_words_b{ Point{50, 250}, 200, 20, "List words starting with input",
		[](Address, Address pw) {reference_to<Querying_window>(pw).list_words(); } },
	list_length_words_b{ Point{300, 250}, 200, 20, "List input length words",
		[](Address, Address pw) {reference_to<Querying_window>(pw).list_length_words(); } },
	result{ Point{100, 300}, 400, 200, "Result: " }
{
	attach(filename);
	attach(set_filename_b);
	attach(quit_b);
	attach(input);
	attach(find_occurence_frequency_b);
	attach(find_most_frequent_b);
	attach(find_longest_b);
	attach(find_shortest_b);
	attach(list_words_b);
	attach(list_length_words_b);
	attach(result);
}

void Querying_window::quit()
{
	hide();
}

void Querying_window::set_filename()
{
	string fn = filename.get_string();
	ifstream ifs{ fn };
	if (!ifs) throw exception("cannot open file");
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	msi.clear();
	for (string s; ifs >> s;)
	{
		++msi[s];
	}
	if (!ifs && !ifs.eof()) throw exception("invalid input");
}

void Querying_window::find_occurence_frequency()
{
	string word = input.get_string();
	result.put(to_string(msi[word]));

	redraw();
}

void Querying_window::find_most_frequent()
{
	set<pair<string, int>, Frequency> spsi{ msi.begin(), msi.end() };
	ostringstream oss;
	oss << spsi.rbegin()->first << ": " << spsi.rbegin()->second << " times";
	result.put(oss.str());

	redraw();
}

void Querying_window::find_longest()
{
	set<pair<string, int>, Size> spsi{ msi.begin(), msi.end() };
	ostringstream oss;
	oss << spsi.rbegin()->first;
	result.put(oss.str());

	redraw();
}
void Querying_window::find_shortest()
{
	set<pair<string, int>, Size> spsi{ msi.begin(), msi.end() };
	ostringstream oss;
	oss << spsi.begin()->first;
	result.put(oss.str());

	redraw();
}

void Querying_window::list_words()
{
	string fs = input.get_string();
	char ch = fs[0];
	auto p = find_if(msi.begin(), msi.end(),
		[&](const pair<string, int>& p) {return p.first.front() == ch; });
	auto q = find_if(msi.rbegin(), msi.rend(),
		[&](const pair<string, int>& p) {return p.first.front() == ch; });
	ostringstream oss;
	do
	{
		oss << p++->first << ' ';
	} while (*p != *q);
	result.put(oss.str());

	redraw();
}

void Querying_window::list_length_words()
{
	int n = input.get_int();
	set<pair<string, int>, Size> spsi{ msi.begin(), msi.end() };
	auto p = find_if(spsi.begin(), spsi.end(),
		[&](const pair<string, int>& p) {return p.first.size() == n; });
	auto q = find_if(spsi.rbegin(), spsi.rend(),
		[&](const pair<string, int>& p) {return p.first.size() == n; });
	ostringstream oss;
	do
	{
		oss << p++->first << ' ';
	} while (*p != *q);
	result.put(oss.str());

	redraw();
}

int main()
try
{
	Querying_window win{ Point{100, 100}, 600, 600, "Query" };
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