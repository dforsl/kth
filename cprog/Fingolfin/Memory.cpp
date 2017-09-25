#include "Memory.h"

using namespace fingolfin::actors::races;

string const Memory::NAME = "Memory";
map<string, double> const Memory::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };

Memory::Memory() : Race(NAME, ATTR_COEFFICIENTS)
{
}

Memory::~Memory()
{
}