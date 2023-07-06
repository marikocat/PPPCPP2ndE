#include "Query.h"

bool Frequency::operator()(const pair<string, int>& p1, const pair<string, int>& p2) const
{
	if (p1.second == p2.second) return p1.first < p2.first;
	else return p1.second < p2.second;
}

bool Size::operator()(const pair<string, int>& p1, const pair<string, int>& p2) const
{
	if (p1.first.size() == p2.first.size()) return p1.first < p2.first;
	else return p1.first.size() < p2.first.size();
}