#include "Container.h"

/*
	因为尝试把container的容器改成map， 但是防止后面需要list的容器，先保留这段代码
void Container::add(int x)
{
	this->space += Resource::item_map[x]->size;
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

void Container::add(int x, int sum)
{
	this->space += sum * Resource::item_map[x]->size;
	for (std::list<std::pair<int, int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		if (it->first == x)
		{
			it->second+=sum;
			return;
		}
	}
	items.push_back(std::make_pair(x, sum));
}

void Container::remove(int x)
{
	this->space -= Resource::item_map[x]->size;
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

void Container::remove(int x, int sum)
{
	this->space -= sum * Resource::item_map[x]->size;
	for (std::list<std::pair<int, int>>::iterator it = items.begin(); it != items.end(); it++)
	{
		if (it->first == x)
		{
			it->second-=sum;
			if (!it->second)
			{
				it = items.erase(it);
			}
			return;
		}
	}
}
*/

void Container::add(std::string name)
{
	this->space += Resource::item_map[Resource::item_map_for_string[name]]->size;
	if (items.find(name) != items.end())
	{
		items[name]++;
	}
	else
	{
		items[name] = 1;
	}
}

void Container::add(std::string name, int sum)
{
	this->space += Resource::item_map[Resource::item_map_for_string[name]]->size * sum;
	if (items.find(name) != items.end())
	{
		items[name] += sum;
	}
	else
	{
		items[name] = sum;
	}
}

bool Container::have(std::string name)
{
	if (items.find(name) == items.end() || items[name] == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Container::have(std::string name, int sum)
{
	if (items.find(name) == items.end() || items[name] < sum)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Container::remove(std::string name)
{
	if (!have(name))return;
	items[name]--;
	this->space -= Resource::item_map[Resource::item_map_for_string[name]]->size;
	if (!items[name])
		items.erase(name);
}

void Container::remove(std::string name, int sum)
{
	if (!have(name, sum))return;
	items[name] -= sum;
	this->space -= Resource::item_map[Resource::item_map_for_string[name]]->size * sum;
	if (!items[name])
		items.erase(name);
}

bool Container::canPut(std::string name)
{
	return this->space + Resource::item_map[Resource::item_map_for_string[name]]->size <= this->capacity;
}

bool Container::canPut(std::string name, int sum)
{
	return this->space + sum * Resource::item_map[Resource::item_map_for_string[name]]->size <= this->capacity;
}

void Container::set(int capacity)
{
	this->capacity = capacity;
}

void Container::set(int space, int capacity)
{
	this->space = space;
	this->capacity = capacity;
}

int Container::getNum(std::string name)
{
	if (items.find(name) == items.end() || items[name] == 0)
	{
		return 0;
	}

	return items[name];
}