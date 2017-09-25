#include "GarbageCollection.h"

using namespace fingolfin::actors::abilities;

string const GarbageCollection::NAME = "Garbage Collection";
string const GarbageCollection::DESCRIPTION = "Releases lost memory.";
Type const GarbageCollection::TYPE = Type::Magic;
int const GarbageCollection::DAMAGE = 30;
int const GarbageCollection::EP = 100;

GarbageCollection::GarbageCollection() : Ability(NAME, DESCRIPTION, TYPE, DAMAGE, EP)
{
}


GarbageCollection::~GarbageCollection()
{
}
