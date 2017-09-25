#ifndef MEMORY_H
#define MEMORY_H

#include "Race.h"

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Memory :
				public Race
			{
				public:
					Memory();
					~Memory();

				private:
					static string const NAME;
					static map<string, double> const ATTR_COEFFICIENTS;
			};
		}
	}
}

#endif