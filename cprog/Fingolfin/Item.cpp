#include "Item.h"

using namespace fingolfin::items;

Item::Item(string const name, int const weight, double const hp_coefficient, double const ep_coefficient) : _name(name), _weight(weight), _hp_coefficient(hp_coefficient), _ep_coefficient(ep_coefficient)
{
}

Item::~Item()
{
}

string const & Item::name() const
{
	return _name;
}

int const & Item::weight() const
{
	return _weight;
}

double const & Item::hp_coefficient() const
{
	return _hp_coefficient;
}

double const & Item::ep_coefficient() const
{
	return _ep_coefficient;
}