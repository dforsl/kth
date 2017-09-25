#ifndef BOSS_H
#define BOSS_H

#include "NPC.h"

namespace fingolfin
{
	namespace actors
	{
		class Boss :
			public NPC
		{
			public:
				Boss(string const &, Race *, Class *, vector<Item const *> &);
				~Boss();
		};

	}
}

#endif