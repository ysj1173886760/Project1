#include "Enemy.h"

inline int abs(int x)
{
	return x >= 0 ? x : -x;
}

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
	PlayerState::player_hp -= this->attack_min;
	return this->attack_min;
}

void zombie::move()
{
	bool flag = true;
	int nx = this->x;
	int ny = this->y;
	if (flag && PlayerState::player_x < this->x)
	{
		nx--;
		if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
		{
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	if (flag && PlayerState::player_x > this->x)
	{
		nx++;
		if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
		{
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	if (flag && PlayerState::player_y < this->y)
	{
		ny--;
		if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
		{
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}

	}
	if (flag && PlayerState::player_y > this->y)
	{
		ny++;
		if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
		{
			flag = false;
			Resource::mainMap[PlayerState::player_position][this->x][this->y] = 0;
			Resource::mainMap[PlayerState::player_position][nx][ny] = this->id;
		}
	}
	this->x = nx;
	this->y = ny;
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