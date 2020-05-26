#pragma once
#include<string>
class Event
{
	public:
		std::string content;
		
		Event(std::string content)
		{
			this->content = content;
		}
		Event()
		{
			this->content = "";
		}
};

