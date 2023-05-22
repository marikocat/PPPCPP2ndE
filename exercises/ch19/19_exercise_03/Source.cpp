#include <iostream>
#include <vector>
using namespace std;

template<typename T, typename U>
class Pair {
public:
	T n;
	U v;
};

int main()
try
{
	vector<Pair<string, double>> v;
	v.push_back({ "var", 10.5 });
	v.push_back({ "const", 100 });
	v.push_back({ "let", 50.89 });

	for (Pair<string, double> p : v)
		cout << p.n << ' ' << p.v << '\n';
}
catch (exception& e)
{
	cerr << "error: " << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}