#include "Simple_window.h"
#include "Graph.h"

int main()
try
{
    using namespace Graph_lib;

    Simple_window win{ Point{100, 100}, 600, 400, "My window" };

    Vector_ref<Graph_lib::Rectangle> matrix;
    for (int i = 0; i < 16; ++i)
        for (int j = 0; j < 16; ++j)
        {
            matrix.push_back(new Graph_lib::Rectangle{ Point{i * 20, j * 20}, 20, 20 });
            //matrix[matrix.size() - 1].set_color(Color{ i * 16 + j });
            matrix[matrix.size() - 1].set_color(Color::invisible);
            matrix[matrix.size() - 1].set_fill_color(Color{ i * 16 + j });
            win.attach(matrix[matrix.size() - 1]);
        }

    win.wait_for_button();
}
catch (exception& e) {
    // some error reporting
    return 1;
}
catch (...) {
    // some more error reporting
    return 2;
}