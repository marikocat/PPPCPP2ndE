#include "..\std_lib_facilities.h"
#include "Math.h"

using namespace Math;

int main()
{
    Rational r{ 456,100 };
    double d = 4.56;

    cout << std::fixed << std::setprecision(20)
        << (r * 100).convert_to_double() << '\n';
    cout << std::fixed << std::setprecision(12)
        << d * 100 << '\n';

    return 0;
}