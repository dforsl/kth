#include "Utils.h"

#include <iostream>
#include <chrono>
#include <string>
#include <thread>

using namespace fingolfin;
using namespace std;

int const Utils::PRINT_PAUSE = 0;

string Utils::read_input()
{
	string input;
	getline(cin, input);

	return input;
}

void Utils::print(string const & str)
{
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		cout << *it;
		this_thread::sleep_for(chrono::milliseconds(PRINT_PAUSE));
	}

	cout << endl;
}

void Utils::print(vector<string> const & list)
{
	int i = 1;
	for (std::vector<string>::const_iterator it = list.begin(); it != list.end(); ++it, ++i)
	{
		Utils::fast_print(to_string(i) + "." + (*it));
	}
}

void Utils::print(vector<Item const *> items)
{
	int i = 1;
	for (std::vector<Item const *>::iterator it = items.begin(); it != items.end(); ++it, ++i)
	{
		Utils::fast_print(to_string(i) + "." + (*it)->name());
		Utils::fast_print("  (weight: " + to_string((*it)->weight()) + ", hp:" + Utils::format((*it)->hp_coefficient()) + ", ep: " + Utils::format((*it)->ep_coefficient()) + ")");
	}
}

void Utils::fast_print(string const & str)
{
	cout << str << endl;
}

vector<string> Utils::tokenize(string const & input)
{
	vector<string> tokens;
	string s;
	for (auto it = input.begin(); it != input.end(); ++it)
	{
		if ((*it) == ' ')
		{
			tokens.push_back(s);
			s = "";
			continue;
		}

		s += *it;
	}
	if (!s.empty())
	{
		tokens.push_back(s);
	}

	return tokens;
}

string Utils::format(double d)
{
	string ds = to_string(d);
	while (ds.rfind('0', -1) == ds.length() - 1)
	{
		ds = ds.substr(0, ds.length() - 1);
	}
	return ds;
}
