#pragma once
#include<string>

class Interaction
{
	public:
		/*
			ǿö������
		*/
		enum class TYPE
		{
			ItemBox,			//����
			Event,				//����ָ���ǿɻ����¼�����������ʾ���¼������е��¼�
			PlaceableEvent,
			Other				//ָ���κ�������������Ʒ
		}type;

		int key;				//��Ӧ�ļ�ֵ
		std::string des;		//�����¼�����

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