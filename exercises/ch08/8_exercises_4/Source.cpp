#include "../std_lib_facilities.h"

void print(const string& label, const vector<int>& data)
// Only read arguments, so it safe to pass them by const-reference
{
    cout << label << ": { ";
    for (int i : data)
        cout << i << ' ';
    cout << "}\n";
}

int check_add(int a, int b)
// Adds two integers performing overflow control to avoid undefined behavior.
{
    if (((b > 0) && (a > (numeric_limits<int>::max() - b))) ||
        ((b < 0) && (a < (numeric_limits<int>::min() - b))))
        error("check_add(): integer add overflows.");
    else
        return a + b;
}

void fibonacci(int x, int y, vector<int>& v, int n)
// Generates a Fibonacci sequence of n values into v, starting with values x
// and y (integers passed by value, and we are modifying v, so it is passed by
// reference).
// Preconditions:
//  Vector must be empty
//  To simplify, n must be equal or greater than two.
{
    if (v.size() != 0)
        error("fibonacci(): Non empty vector passed as argument.");
    if (n < 2)
        error("fibonacci(): n must be al least 2.");

    v.push_back(x);
    v.push_back(y);

    // Add a try-catch block to catch overflow and let the program continue
    try {
        for (int i = 2; i < n; ++i)
            v.push_back(check_add(v[i - 2], v[i - 1]));
    }
    catch (exception& e) {
        cerr << e.what() << '\n';
    }
}

int main()
try {
    vector<int> data;
    int max{ 0 };         // Keep track of maximum int obtained
    int min{ 0 };         // Keep track of minimum int obtained
    int begin{ -100 };    // Value from calculate Fibonacci sequences
    int end{ 100 };       // Value to calculate Fibonacci sequences
    int seq_size{ 50 };   // Elements of Fibonacci sequence

    // Generate Fibonacci sequences
    for (int i = begin; i < end; ++i) {
        fibonacci(i, i + 1, data, seq_size);
        int& val = data[data.size() - 1];
        if (val > max) max = val;
        if (val < min) min = val;
        data.clear();                     // Empty vector for next loop
    }

    cout << "Maximum integer approximate: " << max;
    cout << " (real limit " << numeric_limits<int>::max() << ")\n";
    cout << "Minimum integer approximate: " << min;
    cout << " (real limit " << numeric_limits<int>::min() << ")\n";

    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknwon exception!!\n";
    return 2;
}