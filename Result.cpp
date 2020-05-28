#include "Result.h"


void Result::updateState()
{
	PlayerState::player_food += this->food;
	PlayerState::player_water += this->water;
	PlayerState::player_sanity += this->sanity;
	PlayerState::player_fatigue += this->fatigue;
	Resource::Maintime.add(this->sec, this->min, this->hou);
}