#include "Result.h"


void UpdatePlayerState::do_result()
{
	PlayerState::player_food += this->food;
	PlayerState::player_water += this->water;
	PlayerState::player_sanity += this->sanity;
	PlayerState::player_fatigue += this->fatigue;
	Resource::Maintime.add(this->sec, this->min, this->hou);
}

void OpenCraftWindow::do_result()
{
	UI::open_craft = true;
	UI::craft_name = this->window_name;
}