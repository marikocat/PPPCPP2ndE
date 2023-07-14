#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <regex>
#include <chrono>
using namespace std;

using Line_iter = vector<string>::const_iterator;

class Message
{
	Line_iter first;
	Line_iter last;
public:
	Message(Line_iter p1, Line_iter p2) : first{ p1 }, last{ p2 }{}
	Line_iter begin() const { return first; }
	Line_iter end() const { return last; }
};

using Mess_iter = vector<Message>::const_iterator;

struct Mail_file
{
	string name;
	vector<string> lines;
	vector<Message> m;

	Mail_file(const string& n);

	Mess_iter begin() const { return m.begin(); }
	Mess_iter end() const { return m.end(); }
};

Mail_file::Mail_file(const string& n)
{
	ifstream in{ n }; // open the file
	if (!in)
	{
		cerr << "no " << n << '\n';
		exit(1); // terminate the program
	}

	for (string s; getline(in, s);) // build the vector of lines
		lines.push_back(s);

	auto first = lines.begin(); // build the vector of messages
	for (auto p = lines.begin(); p != lines.end(); ++p)
	{
		if (*p == "----") // end of message
		{
			m.push_back(Message(first, p));
			first = p + 1;
		}
	}
}

int is_prefix(const string& s, const string& p)
{
	int n = p.size();
	if (string(s, 0, n) == p) return n;
	return 0;
}

bool find_from_addr(const Message* m, string& s)
{
	regex pat{ "^From: ([\\w. <>@]*)$" };
	for (const auto& x : *m)
	{
		smatch matches;
		if (regex_match(x, matches, pat))
		{
			s = matches[1];
			return true;
		}
	}
	return false;
}

bool find_addr_from_name(const Message* m, const string& name, string& s)
{
	regex pat{ name };
	for (const auto& x : *m)
	{
		smatch matches;
		if (regex_search(x, matches, pat))
		{
			s = string(x, string("From: ").size());
			return true;
		}
	}
	return false;
}

string find_subject(const Message* m)
{
	regex pat{ "^Subject: (.*)$" };
	for (const auto& x : *m)
	{
		smatch matches;
		if (regex_match(x, matches, pat))
			return matches[1];
	}
	return "";
}

int main()
{
	Mail_file mfile{ "my-mail-file.txt" };

	string sender_name;
	cout << "Enter sender name:\n";
	getline(cin, sender_name);

	string sender_address;
	for (const auto& m : mfile)
	{
		string s;
		if (find_addr_from_name(&m, sender_name, sender_address))
			break;
	}
	cout << "Sender address:\n" << sender_address << "\n\n";


	srand(time(NULL));


	multimap<string, const Message*> sender;
	unordered_multimap<string, const Message*> sender2;

	for (const auto& m : mfile)
	{
		string s;
		if (find_from_addr(&m, s))
		{
			sender.insert(make_pair(s, &m));
			sender2.insert(make_pair(s, &m));
		}
	}

	auto start1 = chrono::system_clock::now();
	cout << "Subjects for " << sender_name << ":\n";
	auto pp = sender.equal_range(sender_address);
	for (auto p = pp.first; p != pp.second; ++p)
	{
		cout << find_subject(p->second) << '\n';
	}
	auto finish1 = chrono::system_clock::now();

	auto start2 = chrono::system_clock::now();
	cout << "Subjects for " << sender_name << ":\n";
	auto pp2 = sender2.equal_range(sender_address);
	for (auto p = pp2.first; p != pp2.second; ++p)
	{
		cout << find_subject(p->second) << '\n';
	}
	auto finish2 = chrono::system_clock::now();

	auto duration1 = chrono::duration_cast<chrono::milliseconds>(finish1 - start1);
	auto duration2 = chrono::duration_cast<chrono::milliseconds>(finish2 - start2);

	cout << "For multimap it took " << duration1.count() << " milliseconds\n";
	cout << "For unordered multimap it took " << duration2.count() << " milliseconds\n";
}