#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
	vector<double> distances;
	double total = 0;
	for (double temp; cin >> temp;)
	{
		distances.push_back(temp);
		total += temp;
	}

	sort(distances.begin(), distances.end());

	cout << "Total distance: " << total << "\n";
	cout << "The smallest distance: " << distances[0] << "\n";
	cout << "The greatest distance: " << distances[distances.size() - 1] << "\n";
	cout << "The mean distance: " << total / distances.size() << "\n";

	return 0;
}