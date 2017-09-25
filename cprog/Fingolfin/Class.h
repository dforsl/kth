#ifndef CLASS_H
#define CLASS_H

#include "Ability.h"
#include "Attack.h"

#include <string>
#include <map>

using namespace std;
using namespace fingolfin::actors::abilities;

namespace fingolfin
{
	namespace actors
	{
		namespace classes
		{
			class Class
			{
				public:
					Class(string const &, double const, double const, map<string, double> const &, map<string, Ability> const &);
					virtual ~Class();

					string const & name(void) const;
					double const hp_regeneration(void) const;
					double const ep_regeneration(void) const;
					double const attr_coefficient(string const &) const;
					map<string, Ability> const & abilities(void) const;
					Ability const & ability(string const &) const;

				private:
					string const _name;
					double const _hp_regeneration;
					double const _ep_regeneration;
					map<string, double> const _attr_coefficients;
					map<string, Ability> const _abilities;
			};
		}
	}
}
#endif