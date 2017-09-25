#ifndef PLAYER_H
#define PLAYER_H

//#include "Character.h"
#include "Ability.h"
#include "Environment.h"
#include "Bag.h"
#include "Utils.h"
#include <string>

using namespace fingolfin::actors::abilities;
using namespace fingolfin::environments;
using namespace fingolfin::items;
using namespace std;

namespace fingolfin
{
	namespace actors 
	{
		class Player :
			public Character
		{
			public:
				Player(string const, Race *, Class *);
				~Player();

				Environment * location() const;
				void set_location(Environment *);
				Environment * move(string dir);

				//interactions
				int const attack(Character *, string const &);

				/*template <typename R2, typename C2>
				void talk_to(Character<R2, C2> const &) const;*/

			private:
				Environment * _location;
		};



		/*
			Implementations
		*/

		Player::Player(string const name, Race * race, Class * clazz) : Character(name, race, clazz, 20)
		{
		}

		Player::~Player()
		{
		}

		Environment * Player::location() const
		{
			return _location;
		}

		void Player::set_location(Environment * env)
		{
			_location = env;
		}

		Environment * Player::move(string dir)
		{
			_location = _location->area()->neighbour(_location, dir);
			_location->on_enter();

			return _location;
		}

		int const Player::attack(Character * enemy, string const & a)
		{
			Ability ability = _class->ability(a);

			if (_current_ep < ability.ep())
			{
				throw 0;
			}

			_current_ep -= ability.ep();

			Utils::fast_print(name() + " hits " + enemy->name() + " with " + ability.name() + " for " + to_string(ability.damage()) + " damage");

			return enemy->attacked(ability);
		}
	}
}

#endif
