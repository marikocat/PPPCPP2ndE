#include <iostream>
#include <vector>
using namespace std;

template<typename T>
istream& operator>>(istream& is, vector<T>& v)
{
	for (T val; is >> val;) v.push_back(val);
	if (!is && !is.eof()) throw exception("invalid input");
	return is;
}

template<typename T>
ostream& operator<<(ostream& os, const vector<T>& v)
{
	for (T el : v) cout << el << ' ';
	return os;
}

int main()
try
{
	vector<int> v;
	cin >> v;
	cout << v << '\n';
}
catch (exception& e)
{
	cerr << e.what() << "\n";
	return 1;
}
catch (...)
{
	cerr << "unknown error\n";
	return 2;
}