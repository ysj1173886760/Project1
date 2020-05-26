#pragma once
#include"Resource.h"
#include"PlayerState.h"

#define BLOCK 24

class Init
{
	public:
		static void init_image();
		static void init_player_state();
		static void init_map();
		static void init_item();
		static void init_loot();
		static void init_data();
};

