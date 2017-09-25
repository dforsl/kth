#include "Pointer.h"

using namespace fingolfin::actors::races;

string const Pointer::NAME = "Pointer";
map<string, double> const Pointer::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };

Pointer::Pointer() : Race(NAME, ATTR_COEFFICIENTS)
{
}

Pointer::~Pointer()
{
}