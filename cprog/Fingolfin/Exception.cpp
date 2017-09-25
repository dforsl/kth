#include "Exception.h"

using namespace fingolfin::actors::abilities;

string const Exception::NAME = "Exception";
string const Exception::DESCRIPTION = "Throws an uncatchable exception, creating an error.";
Type const Exception::TYPE = Type::Magic;
int const Exception::DAMAGE = 25;
int const Exception::EP = 30;

Exception::Exception() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}


Exception::~Exception()
{
}
