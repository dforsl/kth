#include "Noob.h"

using namespace fingolfin::actors::races;

string const Noob::NAME = "n00b";
map<string, double> const Noob::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };

Noob::Noob() : Race(NAME, ATTR_COEFFICIENTS)
{
}

Noob::~Noob()
{
}