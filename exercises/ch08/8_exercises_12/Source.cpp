#include "..\std_lib_facilities.h"

void print_until_s(const vector<string>& v, const string& quit)
{
	for (string s : v) {
		if (s == quit) return;
		cout << s << '\n';
	}
}

void print_until_ss(const vector<string>& v, const string& quit)
{
    bool seen{ false };
    for (string s : v) {
        if (s == quit)
            if (seen) return;
            else seen = true;
        cout << s << '\n';
    }
}

int main()
try
{
    vector<string> test_data{ "1", "2", "3", "4", "5" };
    const vector<string> test_data_c{};
    string quit{ "exit" };

    cout << "\nprint_until_s() tests:\n\n";
    print_until_s({ "Hi!", "Hello", "Bye", "quit", "Until tomorrow" }, "quit");
    print_until_s(test_data, "");
    print_until_s(test_data_c, quit);
    print_until_s({ "quit", "Hello", "Bye", "quit", "Until tomorrow" }, "quit");
    print_until_s({ "Hi!", "Hello", "Bye", "quit", quit }, quit);

    cout << "\nprint_until_ss() tests:\n\n";
    print_until_ss({ "Hi!", "Hello", "Bye", "quit", "Until tomorrow", "quit",
                    "No more" }, "quit");
    print_until_ss({ "Hi!", "Hello", quit, "Bye", "exit", "quit", quit }, quit);

    return 0;
}
catch (exception& e)
{
    cerr << e.what() << '\n';
    return 1;
}
catch (...)
{
    cerr << "Unknown exception!!\n";
    return 2;
}