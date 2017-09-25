#ifndef JAVA_DEVELOPER_H
#define JAVA_DEVELOPER_H

#include "Class.h"

namespace fingolfin
{
	namespace actors
	{
		namespace classes
		{
			class JavaDeveloper :
				public Class
			{
				public:
					JavaDeveloper();
					~JavaDeveloper();

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