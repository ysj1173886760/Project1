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
			Cloth,
			Tool,
			Material,
			Placeable
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
			size 是物品大小
			time 是使用物品时间
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
		virtual bool place()
		{
			/*
				do nothing neither
			*/
			return false;
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
		virtual bool is_material()
		{
			return false;
		}
		virtual bool can_use()
		{
			return false;
		}
		virtual bool is_tool()
		{
			return false;
		}
		virtual bool is_placeable()
		{
			return false;
		}
		virtual bool can_place()
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

		bool can_use()
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

class Material : public Item
{
	public:

		~Material(){}

		Material(){}

		bool is_material()
		{
			return true;
		}

		bool can_use()
		{
			return false;
		}
};

class Tool : public Item
{
	public:
		~Tool(){}
		Tool(){}
	
		bool is_tool()
		{
			return true;
		}

		bool can_use()
		{
			return false;
		}
};

class Placeable : public Item
{
	public:
		~Placeable() {}
		Placeable() {}

		bool is_placeable()
		{
			return true;
		}
		bool can_place()
		{
			return true;
		}
		bool place();
};