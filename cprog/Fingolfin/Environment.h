#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "Character.h"
#include "Item.h"

#include <string>
#include <vector>

using namespace fingolfin::actors;
using namespace fingolfin::items;
using namespace std;

namespace fingolfin
{
	namespace environments
	{
		class Area;
		class Environment
		{
			public:
				Environment(Area *);
				~Environment();

				void set_area(Area *);
				Area const * area(void) const;

				Character * inhabitant(void) const;
					
				void set_boss(Character * &);
				void on_enter(void);

			private:
				Area const * _area;
				Character * _inhabitant;
		};
	}
}

#endif
