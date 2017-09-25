#include "Delete.h"

using namespace fingolfin::actors::abilities;

string const Delete::NAME = "Delete";
string const Delete::DESCRIPTION = "Releases allocated memory.";
Type const Delete::TYPE = Type::Magic;
int const Delete::DAMAGE = 40;
int const Delete::EP = 100;

Delete::Delete() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}


Delete::~Delete()
{
}
