#include "JavaDeveloper.h"
#include "TrialAndError.h"
#include "GarbageCollection.h"

using namespace fingolfin::actors::classes;

string const JavaDeveloper::NAME = "JavaDeveloper";
double const JavaDeveloper::HP_REGENERATION = 0.07;
double const JavaDeveloper::EP_REGENERATION = 0.07;
map<string, double> const JavaDeveloper::ATTR_COEFFICIENTS = { { "hp", 1.2 }, { "ep", 1.5 } };
map<string, Ability> const JavaDeveloper::ABILITIES = { { "attack", Attack() }, { "trialAndError", TrialAndError() }, { "garbageCollection", GarbageCollection() } };

JavaDeveloper::JavaDeveloper() : Class(NAME, HP_REGENERATION, EP_REGENERATION, ATTR_COEFFICIENTS, ABILITIES)
{
}


JavaDeveloper::~JavaDeveloper()
{
}
