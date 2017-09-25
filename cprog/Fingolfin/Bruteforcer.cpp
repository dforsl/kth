#include "Bruteforcer.h"
#include "Attack.h"
#include "TrialAndError.h"
#include "Delete.h"

using namespace fingolfin::actors::classes;

string const Bruteforcer::NAME = "h4xx0r";
double const Bruteforcer::HP_REGENERATION = 0.1;
double const Bruteforcer::EP_REGENERATION = 0.1;
map<string, double> const Bruteforcer::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };
map<string, Ability> const Bruteforcer::ABILITIES = { { "attack", Attack() }, { "trialAndError", TrialAndError() }, { "delete", Delete() } };

Bruteforcer::Bruteforcer() : Class(NAME, HP_REGENERATION, EP_REGENERATION, ATTR_COEFFICIENTS, ABILITIES)
{
}


Bruteforcer::~Bruteforcer()
{
}
