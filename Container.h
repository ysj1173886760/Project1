#pragma once

#include<list>
#include"Resource.h"

class Container
{
	public:
		int space;
		int capacity;
		std::list<std::pair<int, int>> items;		//前一个是id 后一个是数量

		Container()
		{
			this->space = 0;
			this->capacity = 0;
			items.clear();
		}
		Container(int space, int capacity)
		{
			this->space = space;
			this->capacity = capacity;
			items.clear();
		}
		Container(int capacity)
		{
			this->space = 0;
			this->capacity = capacity;
			items.clear();
		}
		void set(int);
		void set(int, int);
		void add(int);
		void remove(int);
		bool canPut(int);
};

