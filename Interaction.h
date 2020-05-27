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
};