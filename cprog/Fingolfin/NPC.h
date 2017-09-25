#ifndef NPC_H
#define NPC_H

#include "Character.h"
#include <string>

using namespace std;

namespace fingolfin
{
	namespace actors 
	{
		class NPC :
			public Character
		{
			public:
				NPC(string const &, Race *, Class *, vector<Item const *> &);
				~NPC();

				//interactions
				int const attack(Character *, string const &);

				/*template <typename R2, typename C2>
				void talk_to(Character<R2, C2> const &) const;*/
		};
	}
}

#endif