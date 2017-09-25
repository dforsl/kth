#include "Environment.h"
#include "Area.h"
#include "Boss.h"

using namespace fingolfin::actors;
using namespace fingolfin::actors::races;
using namespace fingolfin::actors::classes;
using namespace fingolfin::environments;
using namespace std;

Environment::Environment(Area * area) : _area(area), _inhabitant(nullptr)
{
}

Environment::~Environment()
{
	if (_inhabitant != nullptr)
	{
		delete _inhabitant;
	}
}

void Environment::set_area(Area * const area)
{
	_area = area;
}

Area const * Environment::area() const 
{
	return _area;
}

Character * Environment::inhabitant() const
{
	return _inhabitant;
}

void Environment::set_boss(Character * & boss)
{
	_inhabitant = boss;
}

void Environment::on_enter()
{
	if (dynamic_cast<Boss *>(_inhabitant))
	{
		return;
	}

	if (_inhabitant != nullptr && _inhabitant->hp() == 0)
	{
		delete _inhabitant;
		_inhabitant = nullptr;
	}

	if (_inhabitant == nullptr)
	{
		int r = rand() % 100;
		if (r < 67)
		{
			return;
		}

		_inhabitant = _area->generate_mob();
	}

	int r = rand() % 100;

}
