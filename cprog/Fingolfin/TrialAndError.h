#ifndef TRIALANDERROR_H
#define TRIALANDERROR_H

#include "Ability.h"

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class TrialAndError :
				public Ability
			{
				public:
					TrialAndError();
					~TrialAndError();

				private:
					static string const NAME;
					static string const DESCRIPTION;
					static Type const TYPE;
					static int const DAMAGE;
					static int const EP;
			};
		}
	}
}


#endif
