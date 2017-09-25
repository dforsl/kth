#include "World.h"
#include "Pointer.h"
#include "Memory.h"
#include "Template.h"
#include "Haxxor.h"
#include "Guru.h"
#include "Guard.h"
#include "Magician.h"
#include "Boss.h"
#include <string>

using namespace fingolfin::environments;
using namespace fingolfin::actors;
using namespace std;

World::World(vector<Area *> const areas, Environment * start, Environment * final_env, vector<Character *> mini_bosses, Character * main_boss) : _areas(areas), _start(start), _final_env(final_env), _mini_bosses(mini_bosses), _main_boss(main_boss)
{
}

World::~World()
{
	for (auto it = _areas.begin(); it != _areas.end(); ++it)
	{
		delete *it;
	}
}

Environment * World::get_start(void) const
{
	return _start;
}

Environment * World::get_final_env(void) const
{
	return _final_env;
}

bool World::mini_bosses_killed() const
{
	for (auto it = _mini_bosses.begin(); it != _mini_bosses.end(); ++it)
	{
		if ((*it)->hp() > 0)
		{
			return false;
		}
	}
	
	return true;
}

bool World::main_boss_killed(void) const
{
	return _main_boss->hp() <= 0;
}

World const * World::build()
{
	auto areas = vector<Area *>();
	/*
		area 1
	*/
	//create area
	Area * area1 = new Area("The Land of Pointers", "This area is dominated by the Pointers, ruled by the Null Pointer; right hand of the Compiler.", [](void) -> Character *
	{
		vector<Item const *> items;
		int r = rand() % 100;
		if (r < 33)
		{
			items.push_back(new Item("Reference", 1, 1.0, 1.3));
		}
		if (r < 20)
		{
			items.push_back(new Item("Pointer Tutorial", 6, 1.2, 1.0));
		}

		Race * race = new Pointer();
		Class * clazz = nullptr;
		r = rand() % 100;
		if (r < 50)
		{
			clazz = new Guard();
		}
		else 
		{
			clazz = new Magician();
		}

		return new NPC("Wandering Pointer", race, clazz, items);
	});
	areas.push_back(area1);

	//create environments
	Environment * area1_env1 = new Environment(area1);
	Environment * area1_env2 = new Environment(area1);
	Environment * area1_env3 = new Environment(area1);
	Environment * area1_env4 = new Environment(area1);
	Environment * area1_env5 = new Environment(area1);
	Environment * area1_env6 = new Environment(area1);
	Environment * area1_env7 = new Environment(area1);
	area1->add_environments(vector<Environment *> {area1_env1, area1_env2, area1_env3, area1_env4, area1_env5, area1_env6, area1_env7});
	area1->add_neighbour(area1_env1, "south", area1_env3);
	area1->add_neighbour(area1_env2, "east", area1_env3);
	area1->add_neighbour(area1_env3, "north", area1_env1);
	area1->add_neighbour(area1_env3, "east", area1_env4);
	area1->add_neighbour(area1_env3, "west", area1_env2);
	area1->add_neighbour(area1_env4, "south", area1_env6);
	area1->add_neighbour(area1_env4, "east", area1_env5);
	area1->add_neighbour(area1_env4, "west", area1_env3);
	area1->add_neighbour(area1_env5, "west", area1_env4);
	area1->add_neighbour(area1_env6, "north", area1_env4);
	area1->add_neighbour(area1_env6, "south", area1_env7);
	area1->add_neighbour(area1_env7, "north", area1_env6);

	/*
		area 2
	*/
	//create area
	Area * area2 = new Area("The Templated Mountains", "The Templates guard the Mountains, taking orders from the Virtual Template Function.", [](void) -> Character *
	{
		vector<Item const *> items;
		int r = rand() % 100;
		if (r < 7)
		{
			items.push_back(new Item("Compiled Template", 9, 1.8, 1.0));
		}

		Race * race = new Template();
		Class * clazz = nullptr;
		r = rand() % 100;
		if (r < 50)
		{
			clazz = new Guard();
		}
		else
		{
			clazz = new Magician();
		}

		return new NPC("Angry Template", race, clazz, items);
	});
	areas.push_back(area2);

	//register mob generator

	//create environments
	Environment * area2_env1 = new Environment(area2);
	Environment * area2_env2 = new Environment(area2);
	Environment * area2_env3 = new Environment(area2);
	Environment * area2_env4 = new Environment(area2);
	Environment * area2_env5 = new Environment(area2);
	Environment * area2_env6 = new Environment(area2);
	Environment * area2_env7 = new Environment(area2);
	area2->add_environments(vector<Environment *> {area2_env1, area2_env2, area2_env3, area2_env4, area2_env5, area2_env6, area2_env7});
	area2->add_neighbour(area2_env1, "south", area2_env4);
	area2->add_neighbour(area2_env1, "east", area2_env2);
	area2->add_neighbour(area2_env2, "south", area2_env5);
	area2->add_neighbour(area2_env2, "east", area2_env3);
	area2->add_neighbour(area2_env2, "west", area2_env1);
	area2->add_neighbour(area2_env3, "south", area2_env6);
	area2->add_neighbour(area2_env3, "west", area2_env2);
	area2->add_neighbour(area2_env4, "north", area2_env1);
	area2->add_neighbour(area2_env4, "east", area2_env5);
	area2->add_neighbour(area2_env5, "north", area2_env2);
	area2->add_neighbour(area2_env5, "east", area2_env6);
	area2->add_neighbour(area2_env5, "west", area2_env4);
	area2->add_neighbour(area2_env6, "north", area2_env3);
	area2->add_neighbour(area2_env6, "south", area2_env7);
	area2->add_neighbour(area2_env6, "west", area2_env5);
	area2->add_neighbour(area2_env7, "north", area2_env6);

	/*
		area 3
	*/
	//create area
	Area * area3 = new Area("Pools of the Forgotten Memory", "Lost Memory is flooding these lands, pumped out by the Memory Leakage.", [](void) -> Character *
	{
		vector<Item const *> items;
		int r = rand() % 100;
		if (r < 15)
		{
			items.push_back(new Item("Recovered Memory", 5, 1.2, 1.7));
		}
		if (r < 50)
		{
			items.push_back(new Item("Memory Profiler", 2, 1.1, 1.2));
		}

		Race * race = new Memory();
		Class * clazz = nullptr;
		r = rand() % 100;
		if (r < 50)
		{
			clazz = new Guard();
		}
		else
		{
			clazz = new Magician();
		}

		return new NPC("Hiding Memory", race, clazz, items);
	});
	areas.push_back(area3);

	//register mob generator

	//create environments
	Environment * area3_env1 = new Environment(area3);
	Environment * area3_env2 = new Environment(area3);
	Environment * area3_env3 = new Environment(area3);
	Environment * area3_env4 = new Environment(area3);
	Environment * area3_env5 = new Environment(area3);
	Environment * area3_env6 = new Environment(area3);
	Environment * area3_env7 = new Environment(area3);
	area3->add_environments(vector<Environment *> {area3_env1, area3_env2, area3_env3, area3_env4, area3_env5, area3_env6, area3_env7});
	area3->add_neighbour(area3_env1, "south", area3_env4);
	area3->add_neighbour(area3_env1, "east", area3_env2);
	area3->add_neighbour(area3_env2, "south", area3_env5);
	area3->add_neighbour(area3_env2, "west", area3_env1);
	area3->add_neighbour(area3_env3, "east", area3_env4);
	area3->add_neighbour(area3_env4, "north", area3_env1);
	area3->add_neighbour(area3_env4, "south", area3_env7);
	area3->add_neighbour(area3_env4, "east", area3_env5);
	area3->add_neighbour(area3_env4, "west", area3_env3);
	area3->add_neighbour(area3_env5, "north", area3_env2);
	area3->add_neighbour(area3_env5, "east", area3_env6);
	area3->add_neighbour(area3_env5, "west", area3_env4);
	area3->add_neighbour(area3_env6, "west", area3_env5);
	area3->add_neighbour(area3_env7, "north", area3_env5);

	//main boss area
	Area * boss_area = new Area("The Domain of the Compiler", "Description missing.", [](void) -> Character * { return nullptr; });
	areas.push_back(boss_area);
	Environment * boss_area_env = new Environment(boss_area);
	boss_area->add_environment(boss_area_env);

	//connect the areas
	area1->add_neighbour(area1_env7, "west", area2_env3);
	area2->add_neighbour(area2_env3, "east", area1_env7);
	area1->add_neighbour(area1_env7, "east", area3_env3);
	area3->add_neighbour(area3_env3, "west", area1_env7);

	//add main boss
	auto main_boss_drops = vector<Item const *>();
	Character * main_boss = new Boss("The Compiler", new Haxxor(), new Guru(), main_boss_drops);
	boss_area_env->set_boss(main_boss);

	//add mini-bosses
	auto area1_boss_drops = vector<Item const *>();
	area1_boss_drops.push_back(new Item("Null Pointer Shield", 7, 1.6, 1.2));
	Character * area1_boss = new Boss("The Null Pointer", new Pointer(), new Guard(), area1_boss_drops);
	area1_env1->set_boss(area1_boss);

	auto area2_boss_drops = vector<Item const *>();
	area2_boss_drops.push_back(new Item("Virtual Cloak", 4, 1.0, 1.9));
	Character * area2_boss = new Boss("The Virtual Template Function", new Template(), new Magician(), area2_boss_drops);
	area2_env7->set_boss(area2_boss);

	auto area3_boss_drops = vector<Item const *>();
	area3_boss_drops.push_back(new Item("Amazing Memory Plug", 1, 1.5, 1.7));
	Character * area3_boss = new Boss("Memory Leakage", new Memory(), new Guard(), area3_boss_drops);
	area3_env6->set_boss(area3_boss);

	//create the world
	World * world = new World(areas, area1_env5, boss_area_env, vector<Character *>({ area1_boss, area2_boss, area3_boss }), main_boss);

	return world;
}