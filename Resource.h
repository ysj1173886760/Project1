#pragma once
#include<easyx.h>
#include<vector>
#include<queue>
#include<list>
#include<map>
#include"Event.h"
#include"Interaction.h"
#include"InteractiveEvent.h"
#include"Container.h"
#include"GameTime.h"
#include"Item.h"
#include"Craft.h"
#include"Enemy.h"
#include"Astar.h"
#include"Random.h"


class Item;
class Container;
class InteractiveEvent;
class Result;
class Comestible;
class Craft;
class Enemy;
class Astar;
class Random;

struct detail
{
	int x;
	int y;
	std::string name;
};

class Resource
{
	public:
		static IMAGE player;
		static IMAGE state;
		static IMAGE backpack;
		static IMAGE backpack_pointer;
		static IMAGE itemBox;
		static IMAGE eventWindow;
		static IMAGE event_pointer;
		static IMAGE Window;
		static IMAGE craft_window;
		static IMAGE campfire;
		static IMAGE zombie;
		static IMAGE hit;
		static IMAGE equip;
		static IMAGE main;
		static IMAGE begin;
		static IMAGE main_pointer;
		static IMAGE help;
		static IMAGE help_page;

		static std::map<std::string, IMAGE>placeable_map;

		static std::map<std::string, std::vector<detail>>placeable_position;

		/*
			地图数据
		*/

		static std::map<std::string, std::vector<std::vector<int>>>mainMap;

		static std::vector<Item*>item_map;

		static Container player_backpack;

		//static std::queue<Event>Event_queue;
		/*
			因为c++不提供遍历队列的方法，只能pop了再push，到不如直接使用list的迭代器来遍历
		*/
		static std::list<Event>Event_queue;

		static std::vector<Container>itemBox_map;

		static std::vector<Interaction*>interaction_map;

		static std::vector<InteractiveEvent>interactionEvent_map;

		static std::map<std::string, int>item_map_for_string;

		static std::map<std::string, std::vector<Craft*>>craft_map;

		static std::map<std::string, int>placeableId_map;
		
		static GameTime Maintime;

		static std::map<std::string, std::vector<Enemy*>>zombie_map;

		static Astar myAstar;

		static std::map<std::string, IMAGE>map_image;

		static Random myrandom;
};


