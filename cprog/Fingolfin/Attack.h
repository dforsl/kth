#ifndef ATTACK_H
#define ATTACK_H

#include "Ability.h"

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class Attack :
				public Ability
			{
				public:
					Attack();
					~Attack();

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