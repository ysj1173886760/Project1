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
		if (Resource::mainMap[PlayerState::player_position][interact_x][interact_y] == 0)
			pos = PlayerState::player_position;
	}
	/*
		可放置
	*/
	if (pos != "")
	{
		Resource::Maintime.add(this->time, 0, 0);
		Resource::Event_queue.push_back(this->event);
		Resource::mainMap[PlayerState::player_position][interact_x][interact_y] = Resource::placeableId_map[this->name];		//用Interactevent来处理
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

void Cloth::equip()
{
	if (PlayerState::equip[this->where] == "")
	{
		Resource::Maintime.add(this->time, 0, 0);
		PlayerState::equip[this->where] = this->name;
		PlayerState::defense += this->defense;
		PlayerState::bloat += this->bloat;
		Resource::player_backpack.remove(this->name);
	}
	else
	{
		Cloth* temp = (Cloth *)Resource::item_map[Resource::item_map_for_string[PlayerState::equip[this->where]]];
		/*
			先判断剩下的那个能不能放
		*/
		if (Resource::player_backpack.space - this->size + temp->size <= Resource::player_backpack.capacity)
		{
			Resource::Maintime.add(this->time, 0, 0);

			Resource::player_backpack.remove(this->name);
			Resource::player_backpack.add(temp->name);

			PlayerState::bloat -= temp->defense;
			PlayerState::defense -= temp->defense;

			PlayerState::equip[this->where] = this->name;
			PlayerState::defense += this->defense;
			PlayerState::bloat += this->bloat;
		}
	}
}

void Weapon::equip()
{
	if (PlayerState::equip[this->where] == "")
	{
		Resource::Maintime.add(this->time, 0, 0);
		PlayerState::equip[this->where] = this->name;
		PlayerState::attack_max += this->attack_max;
		PlayerState::attack_min += this->attack_min;
		Resource::player_backpack.remove(this->name);
	}
	else
	{
		Weapon* temp = (Weapon*)Resource::item_map[Resource::item_map_for_string[PlayerState::equip[this->where]]];
		/*
			先判断剩下的那个能不能放
		*/
		if (Resource::player_backpack.space - this->size + temp->size <= Resource::player_backpack.capacity)
		{
			Resource::Maintime.add(this->time, 0, 0);

			PlayerState::attack_max -= temp->attack_max;
			PlayerState::attack_min -= temp->attack_min;

			Resource::player_backpack.remove(this->name);
			Resource::player_backpack.add(temp->name);

			PlayerState::equip[this->where] = this->name;
			PlayerState::attack_max += this->attack_max;
			PlayerState::attack_min += this->attack_min;
		}
	}
}

void Backpack::equip()
{
	if (PlayerState::equip[this->where] == "")
	{
		Resource::Maintime.add(this->time, 0, 0);
		PlayerState::equip[this->where] = this->name;
		Resource::player_backpack.capacity += this->capacity;
		PlayerState::bloat += this->bloat;
		Resource::player_backpack.remove(this->name);
	}
	else 
	{
		Backpack* temp = (Backpack *)Resource::item_map[Resource::item_map_for_string[PlayerState::equip[this->where]]];
		/*
			先判断剩下的那个能不能放

		*/
		if (Resource::player_backpack.space - this->size + temp->size <= Resource::player_backpack.capacity - temp->capacity + this->capacity)
		{
			Resource::Maintime.add(this->time, 0, 0);

			PlayerState::bloat -= temp->bloat;
			Resource::player_backpack.capacity -= temp->capacity;

			Resource::player_backpack.remove(this->name);
			Resource::player_backpack.add(temp->name);

			PlayerState::equip[this->where] = this->name;
			Resource::player_backpack.capacity += this->capacity;
			PlayerState::bloat += this->bloat;
		}
	}
}

void Heal::use()
{
	PlayerState::player_hp += this->heal;
	Resource::Maintime.add(this->time, 0, 0);
	Resource::Event_queue.push_back(this->event);
}