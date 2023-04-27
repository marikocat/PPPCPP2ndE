#include "..\std_lib_facilities.h"
#include "Chrono.h"

int main()
{
    constexpr int inc{ 5 };   // These are good values for viewing the results
    constexpr int cols{ 4 };
    int col{ 0 };

    // So test for some years
    for (int i = 1700; i < 2200; i += inc) {
        cout << i << ": ";
        if (Chrono::leapyear(i)) cout << "LEAP year    ";
        else cout << "Common year  ";
        ++col;
        if (col == cols) {
            cout << '\n';
            col = 0;
        }
    }
    cout << '\n';

    return 0;
}