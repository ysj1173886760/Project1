#pragma once
#include<iostream>
#include"Container.h"
#include"InteractiveEvent.h"

class UI
{
	public:
		static bool open_backpack;
		static bool open_itemBox;
		static std::pair<int, int>itemBox_pointer;
		static int backpack_pointer;
		static Container now_itemBox;
		static int interact_key;
		static bool open_event;
		static int event_pointer;
		static InteractiveEvent now_event;
};

