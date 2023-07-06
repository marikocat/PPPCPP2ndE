#pragma once
#include <algorithm>
#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <vector>
using namespace std;

struct Frequency {
	bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) const;
};

struct Size {
	bool operator()(const pair<string, int>& p1, const pair<string, int>& p2) const;
};