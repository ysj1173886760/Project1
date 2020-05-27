#pragma once
#include<string>
#include<vector>
#include"Result.h"
/*
	可交互事件类
*/
class InteractiveEvent
{
	public:
		std::string des;		//对事件的描述
		std::vector<Result> selections;	//储存选项
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

