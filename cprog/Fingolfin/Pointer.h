#ifndef POINTER_H
#define POINTER_H

#include "Race.h"

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Pointer :
				public Race
			{
				public:
					Pointer();
					~Pointer();

				private:
					static string const NAME;
					static map<string, double> const ATTR_COEFFICIENTS;
			};
		}
	}
}

#endif