#ifndef HAXXOR_H
#define HAXXOR_H

#include "Race.h"

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Haxxor :
				public Race
			{
				public:
					Haxxor();
					~Haxxor();

				private:
					static string const NAME;
					static map<string, double> const ATTR_COEFFICIENTS;
			};
		}
	}
}

#endif