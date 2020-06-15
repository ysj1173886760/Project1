#include "Enemy.h"


bool zombie::add_step()
{
	this->step++;
	if (this->step == this->speed)
	{
		this->step = 0;
		return true;
	}
	else return false;
}

int zombie::attack()
{
	int temp = Resource::myrandom.getRandom(this->attack_min, this->attack_max);
	temp -= PlayerState::defense;
	if (temp < 0)temp = 0;
	PlayerState::player_hp -= temp;
	return temp;
}

/*
	Õâ¸ömove¼òÖ±ÄÔÒçÑª
void zombie::move()
{
	bool flag = true;
	int nx = this->x;
	int ny = this->y;
	if (flag && PlayerState::player_x < this->x)
	{
		if (Resource::mainMap[PlayerState::player_position][this->x - 1][this->y] == 0)
		{
			nx--;
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	if (flag && PlayerState::player_x > this->x)
	{
		if (Resource::mainMap[PlayerState::player_position][this->x + 1][this->y] == 0)
		{
			nx++;
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	if (flag && PlayerState::player_y < this->y)
	{
		if (Resource::mainMap[PlayerState::player_position][this->x][this->y - 1] == 0)
		{
			flag = false;
			ny--;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}

	}
	if (flag && PlayerState::player_y > this->y)
	{
		if (Resource::mainMap[PlayerState::player_position][this->x][this->y + 1] == 0)
		{
			flag = false;
			ny++;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	if (!flag)
	{
		this->x = nx;
		this->y = ny;
	}
}
*/
void zombie::move()
{
	Resource::myAstar.reset();
	std::pair<int, int>nxt = Resource::myAstar.calc(this->x, this->y);
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
	this->x = nxt.first;
	this->y = nxt.second;
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = this->id;
}

bool zombie::chaseing()
{
	if ((abs(PlayerState::player_x - this->x) <= this->chaseRange) && (abs(PlayerState::player_y - this->y) <= this->chaseRange))
		return true;
	return false;
}

bool zombie::can_attack()
{
	int sum = 0;
	sum += abs(PlayerState::player_x - this->x);
	sum += abs(PlayerState::player_y - this->y);
	if (sum <= 1)return true;
	else return false;
}

bool hunter::can_attack()
{
	int sum = 0;
	sum += abs(PlayerState::player_x - this->x);
	sum += abs(PlayerState::player_y - this->y);
	if (sum <= 1)return true;
	else return false;
}

bool hunter::add_step()
{
	this->step++;
	if (this->step == this->speed)
	{
		this->step = 0;
		return true;
	}
	else return false;
}

int hunter::attack()
{
	int temp = Resource::myrandom.getRandom(this->attack_min, this->attack_max);
	temp -= PlayerState::defense;
	if (temp < 0)temp = 0;
	PlayerState::player_hp -= temp;
	return temp;
}

void hunter::move()
{
	Resource::myAstar.reset();
	std::pair<int, int>nxt = Resource::myAstar.calc(this->x, this->y);
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
	this->x = nxt.first;
	this->y = nxt.second;
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = this->id;
}

bool hunter::chaseing()
{
	if ((abs(PlayerState::player_x - this->x) <= this->chaseRange) && (abs(PlayerState::player_y - this->y) <= this->chaseRange))
		return true;
	return false;
}

bool tyrant::can_attack()
{
	int sum = 0;
	sum += abs(PlayerState::player_x - this->x);
	sum += abs(PlayerState::player_y - this->y);
	if (sum <= 1)return true;
	else return false;
}

bool tyrant::add_step()
{
	this->step++;
	if (this->step == this->speed)
	{
		this->step = 0;
		return true;
	}
	else return false;
}

int tyrant::attack()
{
	int temp = Resource::myrandom.getRandom(this->attack_min, this->attack_max);
	temp -= PlayerState::defense;
	if (temp < 0)temp = 0;
	PlayerState::player_hp -= temp;
	return temp;
}

void tyrant::move()
{
	Resource::myAstar.reset();
	std::pair<int, int>nxt = Resource::myAstar.calc(this->x, this->y);
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
	this->x = nxt.first;
	this->y = nxt.second;
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = this->id;
}

bool tyrant::chaseing()
{
	if ((abs(PlayerState::player_x - this->x) <= this->chaseRange) && (abs(PlayerState::player_y - this->y) <= this->chaseRange))
		return true;
	return false;
}

bool boss::can_attack()
{
	int sum = 0;
	sum += abs(PlayerState::player_x - this->x);
	sum += abs(PlayerState::player_y - this->y);
	if (sum <= 2)return true;
	else return false;
}

bool boss::add_step()
{
	this->step++;
	if (this->step == this->speed)
	{
		this->step = 0;
		return true;
	}
	else return false;
}

int boss::attack()
{
	int temp = Resource::myrandom.getRandom(this->attack_min, this->attack_max);
	temp -= PlayerState::defense;
	if (temp < 0)temp = 0;
	PlayerState::player_hp -= temp;
	return temp;
}

void boss::move()
{
	Resource::myAstar.reset();
	std::pair<int, int>nxt = Resource::myAstar.calc(this->x, this->y);
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
	this->x = nxt.first;
	this->y = nxt.second;
	Resource::mainMap[PlayerState::player_position][this->x][this->y] = this->id;
}

bool boss::chaseing()
{
	if ((abs(PlayerState::player_x - this->x) <= this->chaseRange) && (abs(PlayerState::player_y - this->y) <= this->chaseRange))
		return true;
	return false;
}