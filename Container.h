#pragma once

#include<list>
#include<map>
#include"Resource.h"

class Container
{
	public:
		int space;		//��ǰ����
		int capacity;	//�������
		//std::list<std::pair<int, int>> items;		//ǰһ����id ��һ��������
		std::map<std::string, int> items;

		Container()
		{
			this->space = 0;
			this->capacity = 0;
			items.clear();
		}
		Container(int space, int capacity)
		{
			this->space = space;
			this->capacity = capacity;
			items.clear();
		}
		Container(int capacity)
		{
			this->space = 0;
			this->capacity = capacity;
			items.clear();
		}

		void set(int);
		void set(int, int);
		void add(std::string);
		void add(std::string, int);
		bool have(std::string);
		bool have(std::string, int);
		void remove(std::string);
		void remove(std::string, int);
		bool canPut(std::string);
		bool canPut(std::string, int);
		int getNum(std::string);
};

