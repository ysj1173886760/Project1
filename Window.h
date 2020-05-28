#pragma once

#include<string>
#include<easyx.h>
#include<conio.h>

class Window
{
	public:
		int x;
		int y;
		int width;
		int height;
		int maxLength;
		std::string des;
		IMAGE img;

		Window()
		{
			this->x = 0;
			this->y = 0;
			this->width = 0;
			this->height = 0;
			this->maxLength = 0;
			this->des = "";
		}
		Window(std::string des)
		{
			this->x = 180;
			this->y = 180;
			this->maxLength = 40;
			this->des = des;
		}

		void show();
		
};

