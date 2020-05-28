#pragma once
#include<string>
#include"PlayerState.h"
#include"Resource.h"
#include"GameTime.h"


class Item
{
	public:
		enum class TYPE
		{
			Equipment,
			Consumables,
			OtherItems
		}type;
		int id;
		int hp;
		int food;
		int water;
		int fatigue;
		int size;
		int time;
		std::string name;
		std::string description;
		std::string event;
		Item(TYPE type, int id, int  hp, int food, int water, int fatigue, int size, int time, std::string name, std::string des, std::string event)
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
			this->size = size;
			this->time = time;
		}
		Item()
		{
			this->type = TYPE::OtherItems;
			this->id = 0;
			this->hp = 0;
			this->food = 0;
			this->water = 0;
			this->fatigue = 0;
			this->size = 0;
			this->name = "";
			this->description = "";
			this->event = "";
			this->time = 0;
		}
		void use();
};

