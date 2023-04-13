#include "..\std_lib_facilities.h"

const int min_hour = 0;
const int max_hour = 23;

const string in_file = "raw_temps.txt";

struct Reading {
	int hour;
	double temperature;
};

ostream& operator<<(ostream& os, Reading& r)
{
	os << r.hour << ' ' << fixed << setprecision(2) << r.temperature;
	return os;
}

istream& operator>>(istream& is, Reading& r)
{
	int hour;
	double temperature;

	is >> hour >> temperature;

	if (!is) return is;
	if (hour < min_hour || hour > max_hour)
	{
		is.clear(ios_base::failbit);
		return is;
	}

	r.hour = hour;
	r.temperature = temperature;
	return is;
}

void fill_vector_from_file(vector<Reading>& readings, const string& filename);
double calculate_mean_temp(const vector<Reading>& readings);
double calculate_median_temp(const vector<Reading>& readings);

int main()
try
{
	vector<Reading> temp_readings;
	fill_vector_from_file(temp_readings, in_file);
	cout << "Mean temperature in the data set is " << fixed << setprecision(2) << calculate_mean_temp(temp_readings) << ".\n";
	cout << "Median temperature in the data set is " << calculate_median_temp(temp_readings) << ".\n";
}
catch (exception& e)
{
	cerr << e.what() << '\n';
	return 1;
}
catch (...)
{
	cerr << "Unknown exception\n";
	return 2;
}

void fill_vector_from_file(vector<Reading>& readings, const string& filename)
{
	ifstream ifs{ filename };
	if (!ifs) error("Cannot open input file ", in_file);
	ifs.exceptions(ifs.exceptions() | ios_base::badbit);

	for (Reading r; ifs >> r;)
		readings.push_back(r);

	if (ifs.eof()) return;
	if (ifs.fail()) error("Wrong input data");
}

double calculate_mean_temp(const vector<Reading>& readings)
{
	double sum{ 0 };
	for (const Reading& r : readings)
		sum += r.temperature;
	return sum / readings.size();
}

double calculate_median_temp(const vector<Reading>& readings)
{
	vector<double> temperatures;
	for (const Reading& r : readings)
		temperatures.push_back(r.temperature);
	sort(temperatures.begin(), temperatures.end());

	if (temperatures.size() % 2 == 0)
		return (temperatures[temperatures.size() / 2] +
			temperatures[temperatures.size() / 2 - 1]) / 2;
	else
		return temperatures[temperatures.size() / 2];
}