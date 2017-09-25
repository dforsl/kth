#ifndef ABILITY_H
#define ABILITY_H

#include <iostream>
#include <string>

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			enum class Type { Physical, Magic };

			class Ability
			{
				public:
					Ability(string const &, string const &, Type const &, int const, int const);
					virtual ~Ability();

					string const & name(void) const;
					string const & description(void) const;
					Type const & type(void) const;
					int const ep(void) const;

					int const damage(void) const;

					friend ostream & operator<<(ostream & os, const Ability & a);

				private:
					string const _name;
					string const _description;
					Type const _type;
					int const _damage;
					int const _ep;
			};
		}
	}
}

#endif
