#pragma once
#include<string>
#include"PlayerState.h"

class Result
{
	public:
		std::string des;		//描述选项
		std::string result;		//描述结果
		
		enum class TYPE
		{
			UpdatePlayerState,
			DoNothing
		}type;

		int food;
		int water;
		int fatigue;
		int sanity;

		Result(std::string des, std::string result, TYPE type, int food, int water, int fatigue, int sanity)
		{
			this->des = des;
			this->result = result;
			this->type = type;
			this->food = food;
			this->water = water;
			this->fatigue = fatigue;
			this->sanity = sanity;
		}
		
		Result()
		{
			this->des = "";
			this->result = "";
			this->type = Result::TYPE::DoNothing;
			this->food = 0;
			this->water = 0;
			this->fatigue = 0;
			this->sanity = 0;
		}

		Result(std::string des)
		{
			this->des = des;
			this->result = "";
			this->type = Result::TYPE::DoNothing;
			this->food = 0;
			this->water = 0;
			this->fatigue = 0;
			this->sanity = 0;
		}

		void updateState();
};

