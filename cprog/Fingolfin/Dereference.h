#ifndef DEREFERENCE_H
#define DEREFERENCE_H

#include "Ability.h"

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class Dereference :
				public Ability
			{
				public:
					Dereference();
					~Dereference();

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