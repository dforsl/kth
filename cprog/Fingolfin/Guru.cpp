#include "Guru.h"
#include "Decompile.h"
#include "Dereference.h"
#include "Delete.h"
#include "Exception.h"

using namespace fingolfin::actors::classes;

string const Guru::NAME = "Guru";
double const Guru::HP_REGENERATION = 0.01;
double const Guru::EP_REGENERATION = 0.08;
map<string, double> const Guru::ATTR_COEFFICIENTS = { { "hp", 2.2 }, { "ep", 2.5 } };
map<string, Ability> const Guru::ABILITIES = { { "decompile", Decompile() }, { "dereference", Dereference() }, { "delete", Delete() }, { "exception", Exception() }, { "attack", Attack() } };

Guru::Guru() : Class(NAME, HP_REGENERATION, EP_REGENERATION, ATTR_COEFFICIENTS, ABILITIES)
{
}


Guru::~Guru()
{
}
