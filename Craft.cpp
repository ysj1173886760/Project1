#include "Craft.h"

/*
	ͬwindow
*/

void out_string2(int x, int y, std::string str)
{
	char buff[100];
	strcpy_s(buff, str.c_str());
	outtextxy(x, y, buff);
}

void Craft::add(std::string name, int sum)
{
	this->need.push_back(std::make_pair(name, sum));
}

bool Craft::can_craft()
{
	for (std::vector<std::pair<std::string, int>>::iterator it = need.begin(); it != need.end(); it++)
	{
		if(!Resource::player_backpack.have(it->first, it->second))
		{
			return false;
		}
	}
	return true;
}

void Craft::craft_item()
{
	if (!can_craft())return;
	//if (!Resource::player_backpack.canPut(this->product))return;
	for (std::vector<std::pair<std::string, int>>::iterator it = need.begin(); it != need.end(); it++)
	{
		//if(Resource::item_map[Resource::item_map_for_string[it->first]]->type == Item::TYPE::Tool)
		Resource::player_backpack.remove(it->first, it->second);
	}
	Resource::Event_queue.push_back(this->event);
	Resource::player_backpack.add(this->product);
	Resource::Maintime.add(this->time, 0, 0);
}

void Craft::show()
{
	std::string temp = "";
	std::string str = Resource::item_map[Resource::item_map_for_string[this->product]]->description;

	int count = 0;
	int now = 0;

	for (int i = 0; i < str.size(); i++)
	{
		if (str[i] & 0x80)
		{
			count += 2;
			temp += str[i];
			temp += str[++i];
		}
		else
		{
			count += 1;
			temp += str[i];
		}
		if (count >= 40)
		{
			count = 0;
			out_string2(360 + 20, 180 + 20 + now * 25, temp);
			now++;
			temp = "";
		}
	}
	if (count != 0)
	{
		count = 0;
		out_string2(360 + 20, 180 +  20 + now * 25, temp);
		now++;
		temp = "";
	}
	now += 2;
	for (int i = 0; i < need.size(); i++)
	{
		std::string name = need[i].first;
		int first = Resource::player_backpack.getNum(need[i].first);
		int second = need[i].second;
		std::string print = name + "     " + std::to_string(first) + "/" + std::to_string(second);
		out_string2(360 + 20, 180 + 20 + now * 25, print);
		now++;
	}
}