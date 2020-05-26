#pragma once
#include<easyx.h>
#include<vector>
#include<queue>
#include"Item.h"
#include"Container.h"
#include"Event.h"
#include"Interaction.h"

class Item;

class Resource
{
	public:
		static IMAGE player;
		static IMAGE school;
		static IMAGE state;
		static IMAGE backpack;
		static IMAGE backpack_pointer;
		static IMAGE itemBox;

		static int school_map[30][30];

		static std::vector<Item>item_map;

		static Container player_backpack;

		//static std::queue<Event>Event_queue;
		/*
			因为c++不提供遍历队列的方法，只能pop了再push，到不如直接使用list的迭代器来遍历
		*/
		static std::list<Event>Event_queue;

		static std::vector<Container>itemBox_map;

		static std::vector<Interaction>interaction_map;
};


