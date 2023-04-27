#include "Math.h"

int main()
try
{
    // Test normalize/reduce/equality
    Math::Rational a{ 25, 12 };
    Math::Rational b{ -50, -24 };
    if (a == b) cout << a << " equals " << b << '\n';
    b = Math::Rational{ 12 };
    if (!(a == b)) cout << a << " does not equal " << b << '\n';

    // Test normalize/reduce
    b = Math::Rational{ 12, -4 };
    cout << "12/(-4) after normalization is " << b << '\n';
    b = Math::Rational{ 120, 90 };
    cout << "120/90 normalized and reduced is " << b << '\n';
    b = Math::Rational{ 90, -120 };
    cout << "90/120 normalized and reduced is " << b << '\n';
    b = Math::Rational{ 1071, 462 };
    cout << "1071/462 normalized and reduced is (should be 51/22) " << b << '\n';
    b = Math::Rational{ -105, 252 };
    cout << "-105/252 normalized and reduced is (should be -5/12) " << b << '\n';

    // Test floating point conversion
    b = Math::Rational{ -100, 3 };
    cout << b << " interpreted as floating point is "
        << b.convert_to_double() << '\n';

    // Test addition
    a = Math::Rational{ 3, 4 };
    b = Math::Rational{ 2, 4 };
    cout << a << " + " << b << " = " << a + b << '\n';
    Math::Rational c;
    Math::Rational d;
    c = Math::Rational{ -123, 42 };
    d = Math::Rational{ 245, 81 };
    cout << c << " + " << d << " = " << c + d << '\n';

    // Test substraction/multiplication/division
    cout << a << " - " << b << " = " << a - b << '\n';
    cout << a << " * " << b << " = " << a * b << '\n';
    cout << a << " / " << b << " = " << a / b << '\n';
    cout << c << " - " << d << " = " << c - d << '\n';
    cout << c << " * " << d << " = " << c * d << '\n';
    cout << c << " / " << d << " = " << c / d << '\n';

    // Test >> operator
    cout << "Type some fractions:\n";
    while (cin >> a) cout << '\t' << a << '\n';
    cout << "Format error or Ctrl+D pressed\n";

    // Forced errors
    //b = Math::Rational{-100, 0};
    //b = Math::Rational{1}/Math::Rational{};

    return 0;
}
catch (Math::Rational::ZeroDenumerator& e)
{
    cerr << "Math::Rational::ZeroQ exception: denominator couldn't be 0.\n";
    return 1;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 2;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 3;
}