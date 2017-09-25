/*
Implementations
*/

#include "Character.h"
#include "Utils.h"
#include <string>

using namespace fingolfin::actors;
using namespace fingolfin;

Character::Character(string const & name, Race * race, Class * clazz, int const bag_weight) : _name(name), _race(race), _class(clazz), _bag(bag_weight), _hp(100), _ep(100)
{
	register_coefficient("hp", (_race->attr_coefficient("hp") * _class->attr_coefficient("hp")));
	_current_hp = _hp;

	register_coefficient("ep", (_race->attr_coefficient("ep") * _class->attr_coefficient("ep")));
	_current_ep = _ep;
}

Character::~Character()
{
	delete _race;
	delete _class;
}

string const & Character::name(void) const
{
	return _name;
}

string const & Character::race_name(void) const
{
	return _race->name();
}

string const & Character::class_name(void) const
{
	return _class->name();
}

int const Character::hp() const
{
	return _current_hp;
}

int const Character::max_hp() const
{
	return _hp;
}

int const Character::ep() const
{
	return _current_ep;
}

int const Character::max_ep() const
{
	return _ep;
}

map<string, Ability> const & Character::abilities() const
{
	return _class->abilities();
}

void Character::pick_up(Item const * item)
{
	_bag.put(item);

	register_coefficient("hp", item->hp_coefficient());
	register_coefficient("ep", item->ep_coefficient());
}

Item const * Character::drop(int index)
{
	Item const * item = _bag.take(index);

	register_coefficient("hp", 1/item->hp_coefficient());
	register_coefficient("ep", 1/item->ep_coefficient());

	return item;
}

int const Character::attacked(Ability & a)
{
	int damage = a.damage();
	_current_hp -= damage;

	if (_current_hp < 0) {
		_current_hp = 0;
	}

	return damage;
}

void Character::on_win()
{
}

Bag & Character::bag()
{
	return _bag;
}

void Character::print_stats() const
{
	Utils::fast_print(_name);
	Utils::fast_print("  hp: " + to_string(_current_hp) + "/" + to_string(_hp));
	Utils::fast_print("  ep: " + to_string(_current_ep) + "/" + to_string(_ep));
}

void Character::tick(bool is_fighting)
{
	if (!is_fighting)
		_current_hp += static_cast<int>(_hp * _class->hp_regeneration());

	_current_ep += static_cast<int>(_ep * _class->ep_regeneration());

	if (_current_hp >= _hp)
	{
		_current_hp = _hp;
	}

	if (_current_ep >= _ep)
	{
		_current_ep = _ep;
	}
}

void Character::register_coefficient(string const & which, double const coefficient)
{
	if (which == "hp")
	{
		_hp = static_cast<int>(_hp * coefficient);
		if (_current_hp > _hp)
		{
			_current_hp = _hp;
		}
	}
	else
	{
		_ep = static_cast<int>(_ep * coefficient);
		if (_current_ep > _ep)
		{
			_current_ep = _ep;
		}
	}
}
