#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
#include <vector>
using namespace std;

int main()
{
	ifstream ifs{ "input.txt"};
	if (!ifs) throw exception("cannot open file");

	vector<double> vd;
	double d;
	while (ifs >> d)
	{
		vd.push_back(d);
	}
	if (!ifs && !ifs.eof()) throw exception("cannot read file");

	for (double d : vd)
		cout << d << ' ';
	cout << '\n';

	vector<int> vi(vd.size());
	copy(vd.begin(), vd.end(), vi.begin());

	for (int i = 0; i < vd.size(); ++i)
		cout << vd[i] << ' ' << vi[i] << '\n';

	double sum = accumulate(vd.begin(), vd.end(), 0.0);
	cout << "Sum of vd: " << sum << '\n';

	int sum2 = accumulate(vi.begin(), vi.end(), 0);
	cout << "The difference between sum and sum2: " << sum - sum2 << '\n';

	reverse(vd.begin(), vd.end());
	for (double d : vd)
		cout << d << '\n';

	double mean = sum / vd.size();
	cout << "Mean value of vd: " << mean << '\n';

	vector<double> vd2(vd.size());
	copy_if(vd.begin(), vd.end(), vd2.begin(), [&](double x) {return x < mean; });
	sort(vd2.begin(), vd2.end());
	vd2.erase(vd2.begin(), vd2.begin() + 6);
	for (double d : vd2)
		cout << d << ' ';
	cout << '\n';
}