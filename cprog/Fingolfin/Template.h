#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "Race.h"

namespace fingolfin
{
	namespace actors
	{
		namespace races
		{
			class Template :
				public Race
			{
				public:
					Template();
					~Template();

				private:
					static string const NAME;
					static map<string, double> const ATTR_COEFFICIENTS;
			};
		}
	}
}

#endif