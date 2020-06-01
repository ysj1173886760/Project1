#pragma once
#include<easyx.h>
#include<vector>
#include<queue>
#include<list>
#include"Event.h"
#include"Interaction.h"
#include"InteractiveEvent.h"
#include"Container.h"
#include"GameTime.h"
#include"Item.h"


class Item;
class Container;
class InteractiveEvent;
class Result;
class Comestible;

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

		static int school_map[30][30];

		static std::vector<Item*>item_map;

		static Container player_backpack;

		//static std::queue<Event>Event_queue;
		/*
			因为c++不提供遍历队列的方法，只能pop了再push，到不如直接使用list的迭代器来遍历
		*/
		static std::list<Event>Event_queue;

		static std::vector<Container>itemBox_map;

		static std::vector<Interaction>interaction_map;

		static std::vector<InteractiveEvent>interactionEvent_map;

		static GameTime Maintime;
};


