#include "Class.h"

using namespace fingolfin::actors::classes;

Class::Class(string const & name, double const hp_regeneration, double const ep_regeneration, map<string, double> const & attr_coefficients, map<string, Ability> const & abilities)
: _name(name), _hp_regeneration(hp_regeneration), _ep_regeneration(ep_regeneration), _attr_coefficients(attr_coefficients), _abilities(abilities)
{

}

Class::~Class()
{
}

string const & Class::name() const
{
	return _name;
}

double const Class::hp_regeneration() const
{
	return _hp_regeneration;
}

double const Class::ep_regeneration() const
{
	return _ep_regeneration;
}

double const Class::attr_coefficient(string const & attr) const
{
	return _attr_coefficients.at(attr); //out_of_range if not found
}

map<string, Ability> const & Class::abilities() const
{
	return _abilities;
}

Ability const & Class::ability(string const & ability) const
{
	return _abilities.at(ability); //out_of_range if not found
}