#pragma once
#include<string>

class PlayerState
{
	public:
		static int player_x;
		static int player_y;
		static int player_hp;
		static int player_food;
		static int player_water;
		static int player_fatigue;
		static std::string player_position;
		static int player_face;
		static int player_sanity;

		static int attack_min;
		static int attack_max;

		static bool chased;
};

