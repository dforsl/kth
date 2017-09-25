#ifndef NOOB_H
#define NOOB_H

#include "Race.h"

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Noob :
				public Race
			{
				public:
					Noob();
					~Noob();

				private:
					static string const NAME;
					static map<string, double> const ATTR_COEFFICIENTS;
			};
		}
	}
}

#endif