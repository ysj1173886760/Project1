#pragma once
#include<string>
#include<vector>
#include"Result.h"
/*
	�ɽ����¼���
*/
class InteractiveEvent
{
	public:
		std::string des;		//���¼�������
		std::vector<Result> selections;	//����ѡ��
		InteractiveEvent(std::string des)
		{
			this->des = des;
			selections.clear();
		}
		InteractiveEvent()
		{
			this->des = "";
			selections.clear();
		}
		void addResult(Result);
};

