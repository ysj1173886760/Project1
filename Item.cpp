#include "Item.h"

void Item::use()
{
	Resource::Event_queue.push_back(this->event);
	PlayerState::player_hp += this->hp;
	PlayerState::player_food += this->food;
	PlayerState::player_water += this->water;
	PlayerState::player_fatigue += this->fatigue;
	PlayerState::player_sanity += this->sanity;
	Resource::Maintime.add(this->time, 0, 0);
}