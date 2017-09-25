#include "Boss.h"

using namespace fingolfin::actors;

Boss::Boss(string const & name, Race * race, Class * clazz, vector<Item const *> & items) : NPC(name, race, clazz, items)
{
}

Boss::~Boss()
{
}
