#include "Container.h"

void Container::add(int x)
{
	for (std::list<std::pair<int, int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		if (it->first == x)
		{
			it->second++;
			return;
		}
	}
	items.push_back(std::make_pair(x, 1));
}
void Container::remove(int x)
{
	for (std::list<std::pair<int, int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		if (it->first == x)
		{
			it->second--;
			if (!it->second)
			{
				it = items.erase(it);
			}
			return;
		}
	}
}

void Container::set(int space, int capacity)
{
	this->space = space;
	this->capacity = capacity;
}