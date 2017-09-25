#ifndef DELETE_H
#define DELETE_H

#include "Ability.h"

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class Delete :
				public Ability
			{
				public:
					Delete();
					~Delete();

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