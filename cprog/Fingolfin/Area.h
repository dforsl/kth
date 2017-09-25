#ifndef AREA_H
#define AREA_H

#include "Environment.h"

#include <string>
#include <map>
#include <vector>
#include <functional>

using namespace std;

namespace fingolfin
{
	namespace environments
	{
		class World;
		class Area
		{
			friend class World;

			public:
				Area(string const &, string const &, function<Character *(void)> const);
				~Area();

				string const & name(void) const;
				string const & description(void) const;

				vector<string> const get_moves(Environment const &) const;
				Environment * neighbour(Environment const *, string const &) const;
				map<string, Environment *> const & neighbours(Environment const *) const;
				Character * generate_mob(void) const;

			private:
				void add_environment(Environment *);
				void add_environments(vector<Environment *>);
				void add_neighbour(Environment *, string const &, Environment *);

				string const _name;
				string const _description;
				map<Environment *, map<string, Environment *>> _map;
				function<Character *(void)> const _generator;
		};
	}
}

#endif
