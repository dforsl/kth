#ifndef MAGICIAN_H
#define MAGICIAN_H

#include "Class.h"

namespace fingolfin
{
	namespace actors
	{
		namespace classes
		{
			class Magician :
				public Class
			{
				public:
					Magician();
					~Magician();

				private:
					static string const NAME;
					static double const HP_REGENERATION;
					static double const EP_REGENERATION;
					static map<string, double> const ATTR_COEFFICIENTS;
					static map<string, Ability> const ABILITIES;
			};
		}
	}
}

#endif