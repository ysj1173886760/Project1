#pragma once
#include<string>
#include"PlayerState.h"
#include"Resource.h"
#include"UI.h"

class UI;

class Result
{
	public:
		std::string des;		//描述选项
		std::string result;		//描述结果
		
		enum class TYPE
		{
			UpdatePlayerState,
			OpenCraftWindow,
			DoNothing,
			Break,
			ChangePos
		}type;

		/*
			time need to use
		*/
		int sec;
		int min;
		int hou;

		virtual ~Result(){}
		Result(std::string des, std::string result, TYPE type, int sec, int min, int hou)
		{
			this->des = des;
			this->result = result;
			this->type = type;
			this->sec = sec;
			this->min = min;
			this->hou = hou;
		}
		
		Result()
		{
			this->des = "";
			this->result = "";
			this->type = Result::TYPE::DoNothing;
			this->sec = 0;
			this->min = 0;
			this->hou = 0;
		}

		Result(std::string des)
		{
			this->des = des;
			this->result = "";
			this->type = Result::TYPE::DoNothing;
			this->sec = 0;
			this->min = 0;
			this->hou = 0;
		}

		virtual void do_result()
		{
			/*
				do nothing
			*/
		}
		virtual bool is_UpdatePlayerState()
		{
			return false;
		}
		virtual bool is_DoNothing()
		{
			return false;
		}
		virtual bool is_OpenCraftWindow()
		{
			return false;
		}
		virtual bool is_Break()
		{
			return false;
		}
		virtual bool is_ChangePos()
		{
			return false;
		}
};

class UpdatePlayerState : public Result
{
	public:
		int food;
		int water;
		int sanity;
		int fatigue;

		~UpdatePlayerState() {}
		UpdatePlayerState()
		{
			this->food = 0;
			this->water = 0;
			this->sanity = 0;
			this->fatigue = 0;
		}
		bool is_UpdatePlayerState()
		{
			return true;
		}
		void do_result();
};

class DoNothing :public Result
{
	public:
		~DoNothing(){}
		DoNothing(){}

		bool is_DoNothing()
		{
			return true;
		}
};

class OpenCraftWindow : public Result
{
	public:
		~OpenCraftWindow() {}
		OpenCraftWindow()
		{
			this->window_name = "";
		}

		std::string window_name;

		bool is_OpenCraftWindow()
		{
			return true;
		}

		void do_result();
};

class Break :public Result
{
	public:
		~Break() {}
		Break() {}

		void do_result();

		bool is_Break()
		{
			return true;
		}
};

class ChangePos :public Result
{
	public:
		~ChangePos() {}
		ChangePos()
		{
			map_name = "";
			x = 0;
			y = 0;
		}
		std::string map_name;
		int x;
		int y;

		bool is_ChangePos()
		{
			return true;
		}

		void do_result();
};