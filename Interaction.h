#pragma once
class Interaction
{
	public:
		/*
			强枚举类型
		*/
		enum class TYPE
		{
			ItemBox,
			Event
		}type;

		int key;
		Interaction(TYPE type, int key)
		{
			this->type = type;
			this->key = key;
		}

		Interaction()
		{
			this->type = TYPE::ItemBox;
			this->key = 0;
		}
};