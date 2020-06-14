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

void Break::do_result()
{
	int interact_x = PlayerState::player_x;
	int interact_y = PlayerState::player_y;

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
	Resource::mainMap[PlayerState::player_position][interact_x][interact_y] = 0;

	for (std::vector<detail>::iterator it = Resource::placeable_position[PlayerState::player_position].begin(); it != Resource::placeable_position[PlayerState::player_position].end();)
	{
		if (it->x == interact_x && it->y == interact_y)
		{
			it = Resource::placeable_position[PlayerState::player_position].erase(it);
		}
		else it++;
	}
}

void ChangePos::do_result()
{
	PlayerState::player_position = this->map_name;
	PlayerState::player_x = this->x;
	PlayerState::player_y = this->y;
}