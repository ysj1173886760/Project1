#pragma once

#include<string>
#include<queue>
#include"PlayerState.h"
#include"Resource.h"

class Enemy
{
	public:
		virtual ~Enemy() {}
		Enemy()
		{
			this->x = 0;
			this->y = 0;
			this->map_name = "";
			this->hp = 0;
			this->attack_min = 0;
			this->attack_max = 0;
			this->speed = 0;
			this->step = 0;
			this->chaseRange = 0;
			this->alive = false;
			this->id = 0;
			this->name = "";
		}

		int x;
		int y;
		std::string map_name;

		std::string name;
		
		int hp;
		int attack_min;
		int attack_max;
		int speed;
		int step;
		int chaseRange;

		bool alive;

		int id;

		enum class TYPE
		{
			zombie
		};

		virtual bool is_zombie()
		{
			return false;
		}

		virtual void move() {}
		virtual int attack()
		{
			return 0;
		}
		virtual bool can_attack()
		{
			return false;
		}
		virtual bool add_step()
		{
			return false;
		}
		virtual bool chaseing()
		{
			return false;
		}
};

class zombie :public Enemy
{
	public:
		~zombie() {}
		zombie() {}

		void move();
		int attack();
		bool can_attack();
		bool add_step();
		bool chaseing();

		bool is_zombie()
		{
			return true;
		}
};