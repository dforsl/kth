#ifndef WORLD_H
#define WORLD_H

#include "Area.h"
#include "Boss.h"
#include <map>
#include <vector>

using namespace std;

namespace fingolfin
{
	namespace environments
	{
		class World
		{
			public:
				static World const * build();
				Environment * get_start(void) const;
				Environment * get_final_env(void) const;

				bool mini_bosses_killed(void) const;
				bool main_boss_killed(void) const;

				~World();

			private:
				World(vector<Area *> const, Environment *, Environment *, vector<Character *>, Character *);
				vector<Area *> _areas;
				Environment * _start;
				Environment * _final_env;

				vector<Character *> _mini_bosses;
				Character * _main_boss;
		};
	}
}

#endif