#ifndef BAG_H
#define BAG_H

#include <vector>
#include "Item.h"

namespace fingolfin {
	namespace items {
		class Bag {
			public:
				Bag(int);
				~Bag();

				int weight(void) const;
				void put(Item const *);
				Item const * take(int);
				vector<Item const *> const & items(void) const;

			private:
				int _weight_limit;
				int _weight;
				vector<Item const *> _items;
		};
	}
}

#endif