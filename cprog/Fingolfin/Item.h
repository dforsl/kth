#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;

namespace fingolfin
{
	namespace items
	{
		class Item
		{
			public:
				Item(string, int, double, double);
				~Item();

				string const & name() const;
				int const & weight() const;
				double const & hp_coefficient() const;
				double const & ep_coefficient() const;

			private:
				string const _name;
				int const _weight;
				double const _hp_coefficient;
				double const _ep_coefficient;
		};
	}
}

#endif