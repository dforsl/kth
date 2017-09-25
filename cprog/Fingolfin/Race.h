#ifndef RACE_H
#define RACE_H

#include <string>
#include <map>

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Race
			{
				public:
					Race(string const &, map<string, double> const &);
					virtual ~Race();

					string const & name(void) const;
					double const attr_coefficient(string const &) const;

				private:
					string const _name;
					map<string, double> const _attr_coefficients;
			};
		}
	}
}

#endif