#include "NPC.h"

#include "Utils.h"

#include <limits>
#include <cstdlib>

using namespace fingolfin::actors;

NPC::NPC(string const & name, Race * race, Class * clazz, vector<Item const *> & items) : Character(name, race, clazz, numeric_limits<int>::max())
{
	for (vector<Item const *>::iterator it = items.begin(); it != items.end(); ++it)
	{
		_bag.put(*it);
	}
}

NPC::~NPC()
{
}

int const NPC::attack(Character * enemy, string const & a)
{
	map<string, Ability> abilities = _class->abilities();

	map<string, Ability>::iterator it;
	while (true) {
		int ability_index = rand() % abilities.size();
		it = abilities.begin();
		for (int i = 0; i < ability_index; i++)
		{
			it++;
		}
		if ((*it).second.ep() <= _current_ep) {
			break;
		}
	}

	_current_ep -= (*it).second.ep();

	Utils::fast_print(name() + " hits " + enemy->name() + " with " + (*it).second.name() + " for " + to_string((*it).second.damage()) + " damage");

	return enemy->attacked((*it).second);
}
