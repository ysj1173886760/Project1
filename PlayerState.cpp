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

int PlayerState::speed = 0;
int PlayerState::step = 0;

bool PlayerState::chased = false;

int PlayerState::bloat = 0;
int PlayerState::defense = 0;
std::map<std::string, bool>PlayerState::debuff;
std::map<std::string, std::string>PlayerState::equip;

int PlayerState::experience = 0;

int PlayerState::kill_zombie = 0;