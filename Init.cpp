#include "Init.h"

void Init::init_image()
{
	loadimage(&Resource::school, _T("Resources\\school.png"));
	loadimage(&Resource::player, _T("Resources\\test.png"));
	loadimage(&Resource::state, _T("Resources\\state.png"));
	loadimage(&Resource::backpack, _T("Resources\\backpack.png"));
	loadimage(&Resource::backpack_pointer, _T("Resources\\backpack_pointer.png"));
	loadimage(&Resource::itemBox, _T("Resources\\itemBox.png"));
	loadimage(&Resource::eventWindow, _T("Resources\\eventWindow.png"));
	loadimage(&Resource::event_pointer, _T("Resources\\event_pointer.png"));
}

void Init::init_player_state()
{
	PlayerState::player_x = 10;
	PlayerState::player_y = 20;
	PlayerState::player_hp = 100;
	PlayerState::player_food = 100;
	PlayerState::player_water = 100;
	PlayerState::player_fatigue = 0;
	PlayerState::player_position = "废弃的学校";
	PlayerState::player_face = 0;
	PlayerState::player_sanity = 100;
}

/*
	0是可以通过的
	1是障碍
	2 到 2147483647 是 可交互物品
*/
void school_init()
{
	try
	{
		std::fstream file;
		file.open("data\\school_map.txt", std::ios::in);

		int x = 0, y = 0;
		while (1)
		{
			file >> x >> y;
			if (file.eof())
				break;
			Resource::school_map[x][y] = 1;
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}

}

void Init::init_map()
{
	school_init();
}


void Init::init_item()
{
	Resource::item_map.clear();
	Resource::item_map.push_back(Item(1, 0, 0, 5, 0, 0, 1, 1, "苹果", "香甜可口的苹果，和牛顿有某种关系", "你吃了个苹果，感觉还不错"));
	Resource::item_map.push_back(Item(1, 1, 0, 0, 5, 0, 1, 1, "矿泉水", "一瓶普通的矿泉水，在这资源匮乏的末世显得异常罕见", "你喝了瓶水，口渴程度有所缓解"));
}

void Init::init_loot()
{
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(0);
	Resource::player_backpack.add(1);
}

void data1()
{
	/*
		2号是垃圾桶  0号容器
	*/
	Resource::school_map[28][19] = 2;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0, "求生欲使你忍住刺鼻的味道翻了翻这个垃圾桶"));
	Container temp(20, 20);
	temp.add(0);
	temp.add(0);
	temp.add(0);
	temp.add(0);
	Resource::itemBox_map.push_back(temp);
}

void data2()
{
	/*
		3号是长椅  0号事件
	*/
	Resource::school_map[10][10] = 3;
	Resource::school_map[11][10] = 3;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::Event, 0, "看起来是个颇具有年代感的长椅"));
	InteractiveEvent temp("应该是一个可以休息的地方");
	Result selection1("在椅子上休息一会儿", "你在椅子上躺了一会儿，感觉还不错", Result::TYPE::UpdatePlayerState, 0, 0, -5, 5);
	Result selection2("算了算了");
	temp.addResult(selection1);
	temp.addResult(selection2);
	Resource::interactionEvent_map.push_back(temp);
}

void Init::init_data()
{
	Resource::Event_queue.clear();

	Resource::itemBox_map.clear();

	/*
		前两个没用，因为下标是从2开始的，前两个用来占位
	*/
	Resource::interaction_map.clear();
	Resource::interaction_map.push_back(Interaction());
	Resource::interaction_map.push_back(Interaction());

	/*
		这里开始添加可互动物品
	*/
	
	data1();
	data2();

}