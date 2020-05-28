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
		int sanity;
		std::string name;
		std::string description;
		std::string event;
		std::string pic_source;
		Item(TYPE type, int id, int  hp, int food, int water, int fatigue, int sanity, int size, int time, std::string name, std::string des, std::string event, std::string pic_source)
		{
			this->type = type;
			this->id = id;
			this->hp = hp;
			this->food = food;
			this->water = water;
			this->fatigue = fatigue;
			this->sanity = sanity;
			this->name = name;
			this->description = des;
			this->event = event;
			this->size = size;
			this->time = time;
			this->pic_source = pic_source;
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
			this->sanity = 0;
			this->name = "";
			this->description = "";
			this->event = "";
			this->time = 0;
			this->pic_source = "";
		}
		Item(std::string name, std::string des, std::string pic_source)
		{
			this->type = TYPE::OtherItems;
			this->name = name;
			this->description = des;
			this->pic_source = pic_source;
		}
		void use();
};

