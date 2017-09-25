#include "TrialAndError.h"

using namespace fingolfin::actors::abilities;

string const TrialAndError::NAME = "Trial And Error";
string const TrialAndError::DESCRIPTION = "Hit the opponent with the force of a panic attack.";
Type const TrialAndError::TYPE = Type::Physical;
int const TrialAndError::DAMAGE = 20;
int const TrialAndError::EP = 50;

TrialAndError::TrialAndError() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}

TrialAndError::~TrialAndError()
{
}
