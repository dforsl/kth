#ifndef GARBAGE_COLLECTION_H
#define GARBAGE_COLLECTION_H

#include "Ability.h"

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class GarbageCollection :
				public Ability
			{
				public:
					GarbageCollection();
					~GarbageCollection();

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