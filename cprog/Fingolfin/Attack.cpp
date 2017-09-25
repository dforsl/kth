#include "Attack.h"

using namespace fingolfin::actors::abilities;

string const Attack::NAME = "Attack";
string const Attack::DESCRIPTION = "Punch the opponent in the face.";
Type const Attack::TYPE = Type::Physical;
int const Attack::DAMAGE = 5;
int const Attack::EP = 0;

Attack::Attack() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}

Attack::~Attack()
{
}