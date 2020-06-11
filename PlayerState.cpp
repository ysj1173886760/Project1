#include "PlayerState.h"

int PlayerState::player_x = 0;
int PlayerState::player_y = 0;
int PlayerState::player_hp = 0;
int PlayerState::player_food = 0;
int PlayerState::player_water = 0;
int PlayerState::player_fatigue = 0;
std::string PlayerState::player_position = "";
int PlayerState::player_face = 0;
int PlayerState::player_sanity = 0;

int PlayerState::attack_max = 0;
int PlayerState::attack_min = 0;

bool PlayerState::chased = false;