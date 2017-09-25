#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Class.h"
#include "Ability.h"
#include "Bag.h"
#include <string>

using namespace fingolfin::actors::races;
using namespace fingolfin::actors::classes;
using namespace fingolfin::actors::abilities;
using namespace fingolfin::items;
using namespace std;

namespace fingolfin
{
	namespace actors 
	{
		class Character
		{
			public:
				Character(string const &, Race *, Class *, int const);
				virtual ~Character();

				string const & name(void) const;
				string const & race_name(void) const;
				string const & class_name(void) const;

				int const hp(void) const;
				int const max_hp(void) const;
				int const ep(void) const;
				int const max_ep(void) const;

				map<string, Ability> const & abilities(void) const;

				void pick_up(Item const *);
				Item const * drop(int);

				virtual int const attack(Character *, string const & = "") = 0;
				int const attacked(Ability & a);
				void on_win(void);
				Bag & bag(void);

				// some printing of information
				void print_stats() const;

				//used on some interval
				void tick(bool);

			protected:
				Race const * _race;
				Class const * _class;
				Bag _bag;
				int _hp;
				int _ep;

				int _current_hp;
				int _current_ep;

			private:
				void register_coefficient(string const &, double const coefficient);

				string const _name;
		};
	}
}

#endif
