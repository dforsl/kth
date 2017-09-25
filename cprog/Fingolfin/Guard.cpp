#include "Guard.h"
#include "Delete.h"
#include "Exception.h"
#include "Dereference.h"

using namespace fingolfin::actors::classes;

string const Guard::NAME = "Guard";
double const Guard::HP_REGENERATION = 0.01;
double const Guard::EP_REGENERATION = 0.01;
map<string, double> const Guard::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };
map<string, Ability> const Guard::ABILITIES = { { "attack", Attack() }, { "delete", Delete() }, { "dereference", Dereference() }, { "exception", Exception() } };

Guard::Guard() : Class(NAME, HP_REGENERATION, EP_REGENERATION, ATTR_COEFFICIENTS, ABILITIES)
{
}


Guard::~Guard()
{
}
