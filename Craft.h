#pragma once
#include"Resource.h"
#include<cstring>

class Craft
{
	public:
		int time;
		std::string product;
		std::vector<std::pair<std::string, int>>need;
		std::string event;

		Craft()
		{
			product = "";
			need.clear();
			event = "";
			time = 0;
		}

		Craft(std::string product, std::string event, int time)
		{
			this->product = product;
			this->event = event;
			this->need.clear();
			this->time = time;
		}
		
		~Craft(){}

		void add(std::string name, int sum);
		bool can_craft();
		void craft_item();
		void show();
};

