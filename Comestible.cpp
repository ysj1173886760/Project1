#include "Comestible.h"


void Comestible::use()
{
	PlayerState::player_fatigue += fagitue;
	PlayerState::player_food += food;
	PlayerState::player_water += water;
	Resource::Maintime.add(this->time, 0, 0);
	Resource::Event_queue.push_back(this->event);
}