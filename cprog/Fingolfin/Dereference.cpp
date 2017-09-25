#include "Dereference.h"

using namespace fingolfin::actors::abilities;

string const Dereference::NAME = "Dereference";
string const Dereference::DESCRIPTION = "Creep under the targets skin.";
Type const Dereference::TYPE = Type::Magic;
int const Dereference::DAMAGE = 40;
int const Dereference::EP = 70;

Dereference::Dereference() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}


Dereference::~Dereference()
{
}
