#pragma once
#include"Item.h"

class Item;

class Comestible : public Item
{
public:

	int food;
	int water;
	int fagitue;

	bool is_food()
	{
		return true;
	}

	void use();

	~Comestible() {}

	Comestible()		//用无参构造
	{
		this->fagitue = 0;
		this->food = 0;
		this->water = 0;
	}


};

