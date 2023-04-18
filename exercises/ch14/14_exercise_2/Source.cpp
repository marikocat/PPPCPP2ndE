#include "Simple_window.h"
#include "Graph.h"

int main()
try
{
	using namespace Graph_lib;

	Circle c{ Point{100, 100}, 50 };
	Circle c2{ Point{200, 200}, 40 };
	//Shape circle = c;
	//c = c2;
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "Unknown exception\n";
	return 2;
}