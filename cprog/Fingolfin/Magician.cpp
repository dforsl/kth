#include "Magician.h"
#include "Delete.h"
#include "Dereference.h"
#include "Exception.h"

using namespace fingolfin::actors::classes;

string const Magician::NAME = "Magician";
double const Magician::HP_REGENERATION = 0.01;
double const Magician::EP_REGENERATION = 0.01;
map<string, double> const Magician::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };
map<string, Ability> const Magician::ABILITIES = { { "attack", Attack() }, { "delete", Delete() }, { "Dereference", Dereference() }, { "exception", Exception() } };

Magician::Magician() : Class(NAME, HP_REGENERATION, EP_REGENERATION, ATTR_COEFFICIENTS, ABILITIES)
{
}


Magician::~Magician()
{
}
