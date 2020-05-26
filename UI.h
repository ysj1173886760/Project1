#pragma once
#include<iostream>
#include"Container.h"

class UI
{
	public:
		static bool open_backpack;
		static bool open_itemBox;
		static std::pair<int, int>itemBox_pointer;
		static int backpack_pointer;
		static Container now_itemBox;
};

