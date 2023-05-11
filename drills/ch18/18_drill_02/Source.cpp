#include <iostream>
#include <vector>
using namespace std;

const int v_size = 10;
vector<int> gv = { 1, 2, 4, 8, 16, 32, 64, 128, 256, 512 };

void f(const vector<int>& v)
{
	vector<int> lv(v_size);
	lv = gv;
	for (int i : lv) cout << i << ' ';
	cout << '\n';
	vector<int> lv2 = v;
	for (int i : lv2) cout << i << ' ';
	cout << '\n';
}

int fact(int i)
{
	if (i == 0) return 1;
	else
		return i * fact(i - 1);
}

int main()
{
	f(gv);
	vector<int> vv;
	for (int i = 0; i < v_size; ++i)
		vv.push_back(fact(i + 1));
	f(vv);
}