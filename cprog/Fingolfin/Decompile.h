#ifndef DECOMPILE_H
#define DECOMPILE_H

#include "Ability.h"

using namespace std;

namespace fingolfin
{
	namespace actors
	{
		namespace abilities
		{
			class Decompile :
				public Ability
			{
				public:
					Decompile();
					~Decompile();

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