#pragma once
#include<string>
#include"PlayerState.h"
#include"Resource.h"

class Item
{
	public:
		int type;
		int id;
		int hp;
		int food;
		int water;
		int fatigue;
		int weight;
		int size;
		std::string name;
		std::string description;
		std::string event;
		Item(int type, int id, int  hp, int food, int water, int fatigue, int weight, int size, std::string name, std::string des, std::string event)
		{
			this->type = type;
			this->id = id;
			this->hp = hp;
			this->food = food;
			this->water = water;
			this->fatigue = fatigue;
			this->name = name;
			this->description = des;
			this->event = event;
		}
		Item()
		{
			this->type = 0;
			this->id = 0;
			this->hp = 0;
			this->food = 0;
			this->water = 0;
			this->fatigue = 0;
			this->weight = 0;
			this->size = 0;
			this->name = "";
			this->description = "";
			this->event = "";
		}
		void use();
};

