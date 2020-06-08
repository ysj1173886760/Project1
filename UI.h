#pragma once
#include<iostream>
#include"Container.h"
#include"InteractiveEvent.h"
#include"Window.h"

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
		static Window now_window;
		static bool open_window;
		static int craft_pointer;
		static bool open_craft;
};

