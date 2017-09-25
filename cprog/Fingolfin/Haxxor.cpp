#include "Haxxor.h"

using namespace fingolfin::actors::races;

string const Haxxor::NAME = "h4xx0r";
map<string, double> const Haxxor::ATTR_COEFFICIENTS = { { "hp", 2.2 }, { "ep", 2.5 } };

Haxxor::Haxxor() : Race(NAME, ATTR_COEFFICIENTS)
{
}

Haxxor::~Haxxor()
{
}