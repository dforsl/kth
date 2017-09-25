#ifndef ARENA_H
#define ARENA_H

#include "Utils.h"
#include "SelectionListUtils.h"
#include "Player.h"
#include "Environment.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>

using namespace fingolfin;
using namespace fingolfin::actors;
using namespace fingolfin::environments;
using namespace std;

namespace fingolfin
{
	namespace moderators
	{
		class Arena
		{
			public:
				Arena(Player *);
				~Arena();
					
				bool const fight(void);

			private:
				Player * _player;

				void loot(Character *);
				void print_abilities(void) const;
		};



		/*
			Implementations
		*/

		Arena::Arena(Player * player) : _player(player)
		{
		}

		Arena::~Arena()
		{
		}

		bool const Arena::fight()
		{
			Character * enemy = _player->location()->inhabitant();

			auto attacker = (Character *) _player;
			auto defender = enemy;
			int enemy_name_length = enemy->name().length();
			int player_name_length = _player->name().length();
			string enemy_name_padding = string(30 - enemy_name_length, ' ');
			string player_name_padding = string(30 - player_name_length, ' ');


			if (enemy == nullptr || enemy->hp() == 0)
			{
				throw 0;
			}

			while (_player->hp() > 0 && enemy->hp() > 0)
			{
				attacker->tick(true);
				defender->tick(true);

				int damage = 0;
				if (attacker == _player)
				{
					Utils::fast_print("Which attack? (type 'help' for assistance) ");

					while (true)
					{
						string input = Utils::read_input();
						if (input == "abilities")
						{
							print_abilities();
							continue;
						}
						else if (input == "run")
						{
							int r = rand() % 100;

							if (r < 40)
							{
								Utils::print("Got away safely...");
								return true;
							}

							Utils::print("Can't escape!");
							break;
						}
						else if (input == "stats")
						{
							//TODO
						}
						else if (input == "help")
						{
							Utils::fast_print("abilites            list your abilities");
							Utils::fast_print("<ability>           attack the enemy with the selected ability");
							Utils::fast_print("run                 try to run away");
							Utils::fast_print("stats               show your hp and ep"); // Onödigt?
							Utils::fast_print("help                show this help");
							continue;
						}

						try
						{
							damage = attacker->attack(defender, input);
							break;
						}
						catch (out_of_range e)
						{
							Utils::fast_print(input + " is not a valid ability, try again!");
						}
						catch (int c)
						{
							Utils::fast_print("You don't have enough ep to use " + input);
						}
					}
				}
				else 
				{
					damage = attacker->attack(defender);

					// Print updated stats
					enemy->print_stats();
					_player->print_stats();
				}

				auto tmp = attacker;
				attacker = defender;
				defender = tmp;
			}

			if (enemy->hp() == 0)
			{
				Utils::print("Enemy slain!");
				loot(enemy);
				
				return true;
			}
			
			Utils::print("You die a pathetic death, your family can no longer show themselves in public");
			return false;
		}

		void Arena::loot(Character * corpse)
		{
			vector<Item const *> loot = corpse->bag().items();

			if (loot.size() == 0)
			{
				Utils::print("The enemy dropped nothing!");
				return;
			}

			Utils::print("The enemy dropped loot! (enter 'help' for options)");
			Utils::print(loot);

			while (true)
			{
				vector<string> tokens = Utils::tokenize(Utils::read_input());
				if (tokens[0] == "drop")
				{
					if (tokens.size() == 1)
					{
						Utils::print("Drop what?");
						continue;
					}

					int i = 0;
					try
					{
						i = stoi(tokens[1]);
					}
					catch (invalid_argument e)
					{
						Utils::print("That is not a number!");
						continue;
					}

					try
					{
						_player->drop(i - 1);
					}
					catch (out_of_range e)
					{
						Utils::print("That is not a valid item!");
					}
				}
				else if (tokens[0] == "pickup")
				{
					if (tokens.size() == 1)
					{
						Utils::print("Pick up what?");
						continue;
					}

					int i = 0;
					try
					{
						i = stoi(tokens[1]);
					}
					catch (invalid_argument e)
					{
						Utils::print("That is not a number!");
						continue;
					}

					Item const * item = nullptr;
					try
					{
						item = corpse->drop(i - 1);
						_player->pick_up(item);
					}
					catch (int nr)
					{
						if(nr == 1)
						{
							Utils::print("That is not a valid item!");
						}
						else
						{
							Utils::print("The item is too heavy!");
							corpse->pick_up(item);
						}
					}
					continue;
				}
				else if (tokens[0] == "done")
				{
					break;
				}
				else if (tokens[0] == "bag")
				{
					Utils::print("Your bag contains: ");
					Utils::print(_player->bag().items());
				}
				else if (tokens[0] == "loot")
				{
					Utils::print("The enemy dropped: ");
					Utils::print(corpse->bag().items());
				}
				else if (tokens[0] == "help")
				{
					Utils::fast_print("pickup <number>     pick up the given item");
					Utils::fast_print("drop <number>       drop the given item");
					Utils::fast_print("bag                 view your bag");
					Utils::fast_print("loot                view the loot");
					Utils::fast_print("done                discard the remaining loot");
				}
				else
				{
					Utils::print("What do you mean?");
				}
			}
		}

		void Arena::print_abilities(void) const
		{
			map<string, Ability> abilities = _player->abilities();
			Utils::fast_print("Your abilities are:");
			for (auto it = abilities.begin(); it != abilities.end(); ++it)
			{
				Utils::fast_print((*it).first);
			}
		}
	}
}

#endif
