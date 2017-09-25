#include "Decompile.h"

using namespace fingolfin::actors::abilities;

string const Decompile::NAME = "Decompile";
string const Decompile::DESCRIPTION = "Decompile the target.";
Type const Decompile::TYPE = Type::Physical;
int const Decompile::DAMAGE = 120;
int const Decompile::EP = 30;

Decompile::Decompile() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}


Decompile::~Decompile()
{
}
