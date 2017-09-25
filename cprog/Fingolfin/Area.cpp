#include "Area.h"

using namespace fingolfin::environments;
using namespace std;

Area::Area(string const & name, string const & description, function<Character *(void)> generator) : _name(name), _description(description), _map(map<Environment *, map<string, Environment *>>()), _generator(generator)
{
	for (auto it = _map.begin(); it != _map.end(); ++it)
	{
		it->first->set_area(this);
	}
}

Area::~Area()
{
	for (auto it = _map.begin(); it != _map.end(); ++it)
	{
		delete (*it).first;
	}

	_map.clear();
}

string const & Area::name() const
{
	return _name;
}

string const & Area::description() const
{
	return _description;
}

vector<string> const Area::get_moves(Environment const & env) const
{
	auto pos = _map.begin();
	for (; pos != _map.end(); ++pos)
	{
		if ((*pos).first == &env)
		{
			break;
		}
	}

	if (pos == _map.end())
	{
		throw 1;// exception("no environment found in area");
	}

	auto dir_map = (*pos).second;
	vector<string> directions;
	for (auto it = dir_map.begin(); it != dir_map.end(); ++it)
	{
		directions.push_back((*it).first);
	}

	return directions;
}

Environment * Area::neighbour(Environment const * env, string const & dir) const
{
	auto pos1 = _map.begin();
	for (; pos1 != _map.end(); ++pos1)
	{
		if ((*pos1).first == env)
		{
			break;
		}
	}

	if (pos1 == _map.end())
	{
		throw 2;//  exception("no environment found in area");
	}

	auto pos2 = (*pos1).second.find(dir);

	if (pos2 == (*pos1).second.end())
	{
		throw 3;//  out_of_range("direction not found for environment");
	}

	return (*pos2).second;
}

map<string, Environment *> const & Area::neighbours(Environment const * env) const
{
	auto pos1 = _map.begin();
	for (; pos1 != _map.end(); ++pos1)
	{
		if ((*pos1).first == env)
		{
			break;
		}
	}

	return pos1->second;
}

Character * Area::generate_mob() const
{
	return _generator();
}

void Area::add_environment(Environment * env)
{
	_map.insert(pair<Environment *, map<string, Environment *>>(env, map<string, Environment *>()));
}

void Area::add_environments(vector<Environment *> envs)
{
	for (auto it = envs.begin(); it != envs.end(); ++it)
	{
		add_environment(*it);
	}
}

void Area::add_neighbour(Environment * env, string const & dir, Environment * neighbour)
{
	auto pos1 = _map.begin();
	for (; pos1 != _map.end(); ++pos1)
	{
		if ((*pos1).first == env)
		{
			break;
		}
	}

	if (pos1 == _map.end())
	{
		throw 4;//  exception("environment not found in area");
	}

	auto pos2 = (*pos1).second.find(dir);

	if (pos2 != (*pos1).second.end())
	{
		throw 5;//  out_of_range("environment already has a neighbour in the given direction");
	}

	pos1->second.insert(pair<string, Environment *>(dir, neighbour));
}
