#include "Race.h"

using namespace fingolfin::actors::races;

Race::Race(string const & name, map<string, double> const & attr_coefficients) : _name(name), _attr_coefficients(attr_coefficients)
{
}

Race::~Race()
{
}

string const & Race::name(void) const
{
	return _name;
}

double const Race::attr_coefficient(string const & attr) const
{
	return _attr_coefficients.at(attr); //out_of_range if not found
}