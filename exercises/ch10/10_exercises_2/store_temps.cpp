#include "..\std_lib_facilities.h"

const int readinds_num = 50;
const int max_hour = 24;
const int max_temperature = 100;

const string out_file = "raw_temps.txt";

struct Reading {
	int hour;
	double temperature;
};

ostream& operator<<(ostream& os, Reading& r)
{
	os << r.hour << ' ' << fixed << setprecision(2) << r.temperature;
	return os;
}

void create_readings(vector<Reading>&);
void fill_file(vector<Reading>&);

int main()
try
{
	vector<Reading> temp_readings;
	create_readings(temp_readings);
	fill_file(temp_readings);
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

void create_readings(vector<Reading>& readings)
{
	for (int i = 0; i < readinds_num; ++i)
	{
		int h = rand() % max_hour;
		double t = rand() % max_temperature +
			rand() % max_temperature / double(max_temperature);
		readings.push_back(Reading{ h, t });
	}
}

void fill_file(vector<Reading>& readings)
{
	ofstream ofs{ out_file };
	if (!ofs) error("Cannot open output file ", out_file);

	for (Reading r : readings)
		ofs << r << '\n';
}