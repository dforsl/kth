#ifndef MOVEMENT_MOD_H
#define MOVEMENT_MOD_H

#include "Player.h"
#include "Environment.h"
#include "Utils.h"

using namespace fingolfin;
using namespace fingolfin::environments;

namespace fingolfin
{
	namespace moderators
	{
		class MovementModerator
		{
			public:
				MovementModerator(Player *);
				~MovementModerator();

				void look() const;
				void move(string &);
				void teleport(Environment *);

			private:
				Player * _player;
		};



		/*
			Implementations
		*/

		MovementModerator::MovementModerator(Player * player) : _player(player)
		{
		}

		MovementModerator::~MovementModerator()
		{
		}
		
		void MovementModerator::look() const
		{
			Environment * env = _player->location();
			Utils::print("You are in " + env->area()->name() + "!\n" + env->area()->description());

			Utils::print("From here, you can move ");
			auto neighbourhood = env->area()->neighbours(env);
			for (auto it = neighbourhood.begin(); it != neighbourhood.end(); ++it)
			{
				Utils::print(it->first + ": " + it->second->area()->name());
			}

			if (env->inhabitant() != nullptr)
			{
				if (env->inhabitant()->hp() > 0)
				{
					if (dynamic_cast<Boss *>(env->inhabitant()))
					{
						Utils::print(env->inhabitant()->name() + " (" + env->inhabitant()->race_name() + ", " + env->inhabitant()->class_name() + ") looks down at you with an evil grin. He's been waiting for you...");
					}
					else
					{
						Utils::print("You also see an angry " + env->inhabitant()->race_name() + " " + env->inhabitant()->class_name() + ".");
					}
				}
				else
				{
					Utils::print("You can also smell a rotten corpse nearby.");
				}
			}
		}

		void MovementModerator::move(string & dir)
		{
			try
			{
				string area_name = _player->location()->area()->name();
				Environment * location = _player->move(dir);
				
				if (location->area()->name() != area_name)
				{
					Utils::print("You have travelled to " + location->area()->name() + "!");
					Utils::print(location->area()->description());
				}

				look();
			}
			catch (int code)
			{
				Utils::print("You can't move " + dir + "!");
			}
		}

		void MovementModerator::teleport(Environment * target)
		{
			_player->set_location(target);
			Utils::print("You have teleported to " + target->area()->name() + "!");
			Utils::print(target->area()->description());
			look();
		}
	}
}

#endif
