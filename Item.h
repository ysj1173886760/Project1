#pragma once
#include<string>
#include"PlayerState.h"
#include"Resource.h"
#include"GameTime.h"


class Item
{
	public:
		enum class TYPE
		{
			Weapon,
			Comestible,
			OtherItems,
			Cloth
		}type;

		int size;
		int time;
		std::string name;
		std::string description;
		std::string event;
		std::string pic_source;

		/*
			name 是物品名字
			des 是物品描述
			event 是使用物品时显示的事件
			pic 是物品图片地址
		*/

		Item(TYPE type, int size, int time, std::string name, std::string des, std::string event, std::string pic_source)
		{
			this->type = type;
			this->name = name;
			this->description = des;
			this->event = event;
			this->size = size;
			this->time = time;
			this->pic_source = pic_source;
		}
		Item()
		{
			this->type = TYPE::OtherItems;
	
			this->size = 0;
			this->name = "";
			this->description = "";
			this->event = "";
			this->time = 0;
			this->pic_source = "";
		}
		Item(std::string name, std::string des, std::string pic_source)
		{
			this->type = TYPE::OtherItems;
			this->name = name;
			this->description = des;
			this->pic_source = pic_source;
		}
		virtual void use()
		{
			/*
				just do nothing
			*/
		}
		/*
			虚析构函数
			防止子类无法析构导致内存泄露
		*/
		virtual ~Item() {}

		/*
			用于判断物品种类的函数
		*/
		virtual bool is_food()
		{
			return false;
		}
		virtual bool is_otherItems()
		{
			return false;
		}
		virtual bool is_weapon()
		{
			return false;
		}
		virtual bool is_cloth()
		{
			return false;
		}
};



class Comestible : public Item
{
public:

	int food;
	int water;
	int fagitue;

	bool is_food()
	{
		return true;
	}

	void use();

	~Comestible() {}

	Comestible()		//用无参构造
	{
		this->fagitue = 0;
		this->food = 0;
		this->water = 0;
	}


};

