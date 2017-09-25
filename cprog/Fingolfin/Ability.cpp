#include "Ability.h"

using namespace fingolfin::actors::abilities;

Ability::Ability(string const & name, string const & description, Type const & type, int damage, int ep) : _name(name), _description(description), _type(type), _damage(damage), _ep(ep)
{
}


Ability::~Ability()
{
}

string const & Ability::name() const {
	return _name;
}

string const & Ability::description() const {
	return _description;
}

Type const & Ability::type() const {
	return _type;
}

int const Ability::ep() const {
	return _ep;
}

int const Ability::damage() const {
	return _damage;
}

ostream & operator<<(ostream & os, const Ability & a)
{
	os << a.name() << " - " << '\n' << a.description();
	return os;
}
