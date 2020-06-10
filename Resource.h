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


class Item;
class Container;
class InteractiveEvent;
class Result;
class Comestible;
class Craft;

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
		static IMAGE school;
		static IMAGE state;
		static IMAGE backpack;
		static IMAGE backpack_pointer;
		static IMAGE itemBox;
		static IMAGE eventWindow;
		static IMAGE event_pointer;
		static IMAGE Window;
		static IMAGE craft_window;
		static IMAGE way_to_school;
		static IMAGE campfire;

		static std::map<std::string, IMAGE>placeable_map;

		static std::map<std::string, std::vector<detail>>placeable_position;

		/*
			地图数据
		*/
		static int school_map[30][30];
		
		static int way_to_school_map[30][30];

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
};


