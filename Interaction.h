#pragma once
#include<string>

class Interaction
{
	public:
		/*
			强枚举类型
		*/
		enum class TYPE
		{
			ItemBox,			//容器
			Event,				//这里指的是可互动事件，而不是显示在事件队列中的事件
			PlaceableEvent,
			Other				//指无任何其他互动的物品
		}type;

		int key;				//对应的键值
		std::string des;		//交互事件描述

		Interaction(TYPE type, int key, std::string des)
		{
			this->type = type;
			this->key = key;
			this->des = des;
		}

		Interaction(std::string des)
		{
			this->type = TYPE::Other;
			this->key = 0;
			this->des = des;
		}

		Interaction()
		{
			this->type = TYPE::Other;
			this->key = 0;
			this->des = "";
		}

		~Interaction() {}

		virtual bool is_ItemBox()
		{
			return false;
		}

		virtual bool is_Event()
		{
			return false;
		}

		virtual bool is_PlaceableEvent()
		{
			return false;
		}
};

class ItemBox : public Interaction
{
	public:
		~ItemBox() {}
		ItemBox() {}

		bool is_ItemBox()
		{
			return true;
		}
};

class InteractEvent :public Interaction
{
	public:
		~InteractEvent() {}
		InteractEvent() {}

		bool is_Event()
		{
			return true;
		}
};

class PlaceableEvent :public Interaction
{
	public:
		~PlaceableEvent() {}
		PlaceableEvent()
		{
			this->name = "";
		}

		std::string name;

		bool is_PlaceableEvent()
		{
			return true;
		}
};