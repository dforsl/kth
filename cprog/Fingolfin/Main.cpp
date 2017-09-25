#include "World.h"
#include "Arena.h"
#include "MovementModerator.h"
#include "Haxxor.h"
#include "Noob.h"
#include "Bruteforcer.h"
#include "JavaDeveloper.h"
#include "Utils.h"
#include "SelectionListUtils.h"

#include <iostream>
#include <algorithm>

using namespace fingolfin;
using namespace fingolfin::environments;
using namespace fingolfin::actors;
using namespace fingolfin::actors::races;
using namespace fingolfin::actors::classes;
using namespace fingolfin::moderators;

using namespace std;

Player * create_player(string const & name, string const & race_name, string const & class_name)
{
	Race * race = nullptr;
	Class * clazz = nullptr;

	if (race_name == "h4xx0r")
	{
		race = new Haxxor();
	}
	else if (race_name == "n00b")
	{
		race = new Noob();
	}

	if (class_name == "Bruteforcer")
	{
		clazz = new Bruteforcer();
	}
	if (class_name == "JavaDeveloper")
	{
		clazz = new JavaDeveloper();
	}

	if (race == nullptr || clazz == nullptr)
	{
		throw "couldn't create player";
	}

	return new Player(name, race, clazz);
}


Player * start()
{
	vector<string> const races = { "h4xx0r", "n00b" };
	vector<string> const classes = { "Bruteforcer", "JavaDeveloper" };

	Utils::print("Welcome to the game Game!");
	Utils::print("What's your name?");
	string name = Utils::read_input();
	Utils::print("Welcome, " + name + "!");

	Utils::print("Which race would you like to be? The existing races are:");	
	string race = races[SelectionListUtils::get_selected_item(races)];

	
	Utils::print("Which class would you like to be?  The existing classes are:");
	string clazz = classes[SelectionListUtils::get_selected_item(classes)];

	Utils::print("So, " + name + ", you are a(n) " + race + " " + clazz + "!");
	Utils::print("Let's begin!");

	return create_player(name, race, clazz);
}

void print_prologue(Character * player) {
	string text = "Welcome, brave " + player->race_name() + "!\n";
	text += "This was once a pleasant land, with only a few Exceptions.\n";
	text += "But the Compiler has tricked us, with his many deceptions.\n";
	text += "Since they arrived onto our domain, our problems have ++.\n";
	text += "Terror is everywhere, many loved ones has deceased.\n";
	text += "Our land has become a void, noone alive for miles.\n";
	text += "Our last hope, is that this application compiles.\n";
	text += "So hear our cry for help, and free our beautiful land.\n";
	text += "We would be very grateful, if you could lend a hand.";
	Utils::print(text);
}

void print_help(bool can_teleport)
{
	Utils::fast_print("look                look around in your environment");
	Utils::fast_print("move <direction>    move in the given direction");
	Utils::fast_print("attack              attack a nearby enemy");
	Utils::fast_print("help                this help section");
	if (can_teleport)
	{
		Utils::fast_print("teleport            teleport to the final boss area");
	}
	Utils::fast_print("quit                quit the game");
}

void run()
{
	auto player = start();

	World const * world = World::build();
	player->set_location(world->get_start());

	MovementModerator movement_mod = MovementModerator(player);
	Arena arena = Arena(player);

	print_prologue(player);

	bool can_teleport = false;
	while (true)
	{
		string input = Utils::read_input();

		if (input == "quit")
		{
			break;
		}
		else if (input == "help")
		{
			print_help(can_teleport);
			continue;
		}

		vector<string> tokens = Utils::tokenize(input);
		if (tokens.size() == 0)
		{
			Utils::print("Come again?");
			continue;
		}

		if (tokens[0] == "look")
		{
			movement_mod.look();
		} 
		else if (tokens[0] == "move")
		{
			if (tokens.size() == 1)
			{
				Utils::print("Move where?");
				continue;
			}

			movement_mod.move(tokens[1]);
			player->tick(false);

			continue;
		}
		else if (tokens[0] == "teleport" && can_teleport)
		{
			movement_mod.teleport(world->get_final_env());
		}
		else if (tokens[0] == "fight")
		{
			try
			{
				if (arena.fight())
				{
					if (world->main_boss_killed())
					{
						Utils::print("The Compiler has been defeated and life can finally return to our realm. Well done!");
						break;
					}
					if (!can_teleport && world->mini_bosses_killed())
					{
						can_teleport = true;
					}
					continue;
				}
				else
				{
					break;
				}
			}
			catch (int c)
			{
				Utils::print("There is no one to fight");
			}
		}
		else if (tokens[0] == "bag")
		{
			Utils::print(player->bag().items());
		}
		else if (tokens[0] == "drop")
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
				player->drop(i - 1);
			}
			catch (out_of_range e)
			{
				Utils::print("That is not a valid item!");
			}
		}
		else if (tokens[0] == "stats")
		{
			int player_name_length = player->name().length();
			string player_name_padding = string(30 - player_name_length, ' ');
			player->print_stats();
		}
	}

	cout << "Cleaning up..." << endl;

	delete player;
	delete world;
}

int main() 
{
	run();

	return 0;
}
