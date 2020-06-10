#include "Item.h"


void Comestible::use()
{
	PlayerState::player_fatigue += fagitue;
	PlayerState::player_food += food;
	PlayerState::player_water += water;
	Resource::Maintime.add(this->time, 0, 0);
	Resource::Event_queue.push_back(this->event);
}

bool Placeable::place()
{
	int interact_x = PlayerState::player_x;
	int interact_y = PlayerState::player_y;
	std::string pos = "";

	switch (PlayerState::player_face)
	{
		case 1:
			interact_x--;
			break;
		case 3:
			interact_x++;
			break;
		case 2:
			interact_y--;
			break;
		case 0:
			interact_y++;
			break;
	}
	if (interact_x >= 0 && interact_x <= 29 && interact_y >= 0 && interact_y <= 29)
	{
		if (PlayerState::player_position == "废弃的学校" && Resource::school_map[interact_x][interact_y] == 0)
			pos = "废弃的学校";
		else if (PlayerState::player_position == "通往学校的路" && Resource::way_to_school_map[interact_x][interact_y] == 0)
			pos = "通往学校的路";
	}
	/*
		可放置
	*/
	if (pos != "")
	{
		Resource::Maintime.add(this->time, 0, 0);
		Resource::Event_queue.push_back(this->event);
		if (pos == "废弃的学校")
			Resource::school_map[interact_x][interact_y] = Resource::placeableId_map[this->name];		//用Interactevent来处理
		else if (pos == "通往学校的路")
			Resource::way_to_school_map[interact_x][interact_y] = Resource::placeableId_map[this->name];
		detail temp;
		temp.x = interact_x;
		temp.y = interact_y;
		temp.name = this->name;
		Resource::placeable_position[pos].push_back(temp);
		return true;
	}
	else
	{
		std::string info;
		info = "有障碍物无法放置";
		Resource::Event_queue.push_back(info);
		
	}
	return false;
}