#include "Template.h"

using namespace fingolfin::actors::races;

string const Template::NAME = "Template";
map<string, double> const Template::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };

Template::Template() : Race(NAME, ATTR_COEFFICIENTS)
{
}

Template::~Template()
{
}