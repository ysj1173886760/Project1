#pragma once
#include<iostream>
#include"Container.h"
#include"Window.h"
#include"InteractiveEvent.h"

class Container;
class InteractiveEvent;
class Window;
class Result;

class UI
{
	public:
		static bool open_backpack;
		static bool open_itemBox;
		static std::pair<int, int>itemBox_pointer_left;
		static std::pair<int, int>itemBox_pointer_right;
		static int itemBox_pointer;
		static std::pair<int, int> backpack_pointer;
		static Container now_itemBox;
		static int interact_key;
		static bool open_event;
		static int event_pointer;
		static InteractiveEvent now_event;
		static Window now_window;
		static bool open_window;
		static std::pair<int, int>craft_pointer;
		static bool open_craft;
		static std::string craft_name;
		static int equip_pointer;
		static bool open_equip;
};

