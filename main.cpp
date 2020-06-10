#define _CRT_SECURE_NO_WARNINGS
#define BACKPACK_X 180
#define BACKPACK_Y 180

/*
	b*[^:b#/]+.*$
	json代码8115
*/

#include <easyx.h>			// 引用图形库头文件
#include <conio.h>
#include<string>
#include<cstring>
#include<iostream>
#include "head.h"
#pragma comment( lib, "MSIMG32.LIB")


void out_number(int x, int y, int num)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), num);		// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x, y, s);
}

void out_string(int x, int y, std::string str)
{
	char buff[100];
	strcpy_s(buff, str.c_str());
	outtextxy(x, y, buff);
}
/*
//		dstimg: 目标 IMAGE 对象指针。NULL 表示默认窗体
//		x, y:	目标贴图位置
//		srcimg: 源 IMAGE 对象指针。NULL 表示默认窗体
//		transparentcolor: 透明色。srcimg 的该颜色并不会复制到 dstimg 上，从而实现透明贴图
*/

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor = 0)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// 使用 Windows GDI 函数实现透明位图
	TransparentBlt(dstDC, x, y, w, h, srcDC, 0, 0, w, h, transparentcolor);
}

void use_item()
{
	if (Resource::player_backpack.items.size() == 0)
		return;
	int now = 0;
	
	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		if (now == UI::backpack_pointer)
		{
			Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			if (temp->can_use())
			{
				temp->use();
				Resource::player_backpack.remove(it->first);
				if (Resource::player_backpack.items.size() <= UI::backpack_pointer)		//修改了一个小bug
					UI::backpack_pointer = 0;
			}
			else if (temp->can_place())
			{
				if(temp->place())
					Resource::player_backpack.remove(it->first);
				if (Resource::player_backpack.items.size() <= UI::backpack_pointer)
					UI::backpack_pointer = 0;
			}
			return;
		}
		now++;
	}
}

/*
	操作可交互物品
*/
void interact()
{
	int interact_x = PlayerState::player_x;
	int interact_y = PlayerState::player_y;
	
	switch (PlayerState::player_face)
	{
		case 1:
			interact_x--;
			break;
		case 3:
			interact_x++;
			break;
		case 2:
			interact_y--;
			break;
		case 0:
			interact_y++;
			break;
	}

	if (interact_x >= 0 && interact_x <= 29 && interact_y >= 0 && interact_y <= 29)
	{
		if (PlayerState::player_position == "废弃的学校" && Resource::school_map[interact_x][interact_y] >= 2)
		{
			Interaction *temp = Resource::interaction_map[Resource::school_map[interact_x][interact_y]];
			Interaction::TYPE type = temp->type;
			Resource::Event_queue.push_back(temp->des);

			if (type == Interaction::TYPE::ItemBox)
			{
				UI::now_itemBox = Resource::itemBox_map[temp->key];
				UI::interact_key = temp->key;
				UI::open_itemBox = true;
				UI::itemBox_pointer.first = 0;
				UI::itemBox_pointer.second = 0;
			}
			else if (type == Interaction::TYPE::Event || type == Interaction::TYPE::PlaceableEvent)
			{
				UI::open_event = true;
				UI::event_pointer = 0;
				UI::now_event = Resource::interactionEvent_map[temp->key];
			}
		}
		
	}
}
/*
	移动物品
*/
void move_item()
{
	int now = 0;

	if (UI::itemBox_pointer.first == 0)			//背包移动到物品箱中
	{
		for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
		{
			if (now == UI::itemBox_pointer.second)
			{
				if (Resource::itemBox_map[UI::interact_key].canPut(it->first))
				{
					Resource::itemBox_map[UI::interact_key].add(it->first);
					Resource::player_backpack.remove(it->first);
				}

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//把物品信息更新
				if (Resource::player_backpack.items.size() <= UI::itemBox_pointer.second)
				{
					UI::itemBox_pointer.second = 0;
				}
				return;
			}
			now++;
		}
	}
	else										//物品箱移动到背包
	{
		for (std::map<std::string, int>::iterator it = UI::now_itemBox.items.begin(); it != UI::now_itemBox.items.end(); it++)
		{
			if (now == UI::itemBox_pointer.second)
			{
				if (Resource::player_backpack.canPut(it->first))
				{
					Resource::player_backpack.add(it->first);
					Resource::itemBox_map[UI::interact_key].remove(it->first);
				}

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//把物品信息更新
				if (UI::now_itemBox.items.size() <= UI::itemBox_pointer.second)
				{
					UI::itemBox_pointer.second = 0;
				}
				return;
			}
			now++;
		}
	}
}
/*
	绘制放置物品
*/
void draw_placeable()
{
	for (int i = 0; i < Resource::placeable_position[PlayerState::player_position].size(); i++)
	{
		detail temp = Resource::placeable_position[PlayerState::player_position][i];
		transparentimage(NULL, temp.x * BLOCK, temp.y * BLOCK, &Resource::placeable_map[temp.name]);
	}
}

/*
	为窗口初始化
*/
void initWindow()
{
	int now = 0;
	std::string des;
	std::string source;

	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		if (now == UI::backpack_pointer)
		{
			Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			des = temp->description;
			source = temp->pic_source;
			break;
		}
		now++;
	}

	/*
		图片是70 130
	*/

	char buff[100];
	strcpy(buff, source.c_str());
	loadimage(&UI::now_window.img, buff);
	UI::now_window.des = des;
}

/*
	显示window
*/
void draw_window()
{
	putimage(180, 180, &Resource::Window);
	UI::now_window.show();
}

/*
	显示时间窗口
*/
void do_event()
{
	for (int i = 0; i < UI::now_event.selections.size(); i++)
	{
		if (i == UI::event_pointer)
		{
			if (UI::now_event.selections[i]->type == Result::TYPE::UpdatePlayerState)
			{
				UI::now_event.selections[i]->do_result();
				Resource::Event_queue.push_back(UI::now_event.selections[i]->result);
			}
			else if (UI::now_event.selections[i]->type == Result::TYPE::OpenCraftWindow)
			{
				UI::now_event.selections[i]->do_result();
			}
			else if (UI::now_event.selections[i]->type == Result::TYPE::DoNothing)
			{
				//just do nothing
			}
			
			return;
		}
	}
}

void craft()
{
	Resource::craft_map[UI::craft_name][UI::craft_pointer]->craft_item();
}

void updateWithInput()
{
	if (UI::open_window)
	{
		if (KEYDOWN('X') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_window = false;
		}
	}
	else if (UI::open_backpack)
	{
		if (KEYDOWN('W'))
		{
			if (UI::backpack_pointer - 1 >= 0)
				UI::backpack_pointer--;
		}
		else if (KEYDOWN('S'))
		{
			if (UI::backpack_pointer + 1 < int(Resource::player_backpack.items.size()))
				UI::backpack_pointer++;
		}
		else if (KEYDOWN('F'))
		{
			use_item();
		}
		else if (KEYDOWN('E') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_backpack = false;
			UI::backpack_pointer = 0;
		}
		else if (KEYDOWN('X'))
		{
			UI::open_window = true;
			initWindow();
		}
	}
	else if(UI::open_itemBox)
	{
		if (KEYDOWN('W'))
		{
			if (UI::itemBox_pointer.second- 1 >= 0)
				UI::itemBox_pointer.second--;
		}
		else if (KEYDOWN('S'))
		{
			if (UI::itemBox_pointer.first == 1)
			{
				if (UI::itemBox_pointer.second + 1 < int(UI::now_itemBox.items.size()))
					UI::itemBox_pointer.second++;
			}
			else
				if (UI::itemBox_pointer.second + 1 < int(Resource::player_backpack.items.size()))
					UI::itemBox_pointer.second++;
				
		}
		else if (KEYDOWN('D'))
		{
			if (UI::itemBox_pointer.first == 0)
				UI::itemBox_pointer.first = 1;
		}
		else if (KEYDOWN('A'))
		{
			if (UI::itemBox_pointer.first == 1)
				UI::itemBox_pointer.first = 0;
		}
		else if (KEYDOWN('E') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_itemBox = false;
		}
		else if (KEYDOWN('F'))
		{
			move_item();
		}
	}
	else if (UI::open_event)
	{
		if (KEYDOWN('W'))
		{
			if (UI::event_pointer - 1 >= 0)
				UI::event_pointer--;
		}
		else if (KEYDOWN('S'))
		{
			if (UI::event_pointer + 1 < UI::now_event.selections.size())
				UI::event_pointer++;
		}
		else if (KEYDOWN('F'))
		{
			do_event();
			UI::open_event = false;
		}
	}
	else if (UI::open_craft)
	{
		if (KEYDOWN('T') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_craft = false;
		}
		else if (KEYDOWN('W'))
		{
			if (UI::craft_pointer - 1 >= 0)
				UI::craft_pointer--;
		}
		else if (KEYDOWN('S'))
		{
			if (UI::craft_pointer + 1 < Resource::craft_map[UI::craft_name].size())
				UI::craft_pointer++;
		}
		else if (KEYDOWN('F'))
		{
			craft();
		}
	}
	else
	{
		int nx = PlayerState::player_x;
		int ny = PlayerState::player_y;
		bool flag = false;

		if (KEYDOWN('A'))
		{
			nx--;
			PlayerState::player_face = 1;
		}
		else if (KEYDOWN('D'))
		{
			nx++;
			PlayerState::player_face = 3;
		}
		else if (KEYDOWN('W'))
		{
			ny--;
			PlayerState::player_face = 2;
		}
		else if (KEYDOWN('S'))
		{
			ny++;
			PlayerState::player_face = 0;
		}
		else if (KEYDOWN('F'))
		{
			interact();
		}
		else if (KEYDOWN('E'))
		{
			UI::open_backpack = true;
		}
		else if (KEYDOWN('T'))
		{
			UI::open_craft = true;
			UI::craft_name = "player";
			UI::craft_pointer = 0;
		}
		else if (KEYDOWN(VK_UP))
		{
			PlayerState::player_face = 2;
		}
		else if (KEYDOWN(VK_DOWN))
		{
			PlayerState::player_face = 0;
		}
		else if(KEYDOWN(VK_LEFT))
		{
			PlayerState::player_face = 1;
		}
		else if (KEYDOWN(VK_RIGHT))
		{
			PlayerState::player_face = 3;
		}
		if (nx >= 0 && nx <= 29 && ny >= 0 && ny <= 29)			//移动信息
		{
			if ((PlayerState::player_position == "废弃的学校") && (Resource::school_map[nx][ny] == 0))
				flag = true;
			else if ((PlayerState::player_position == "通往学校的路") && (Resource::way_to_school_map[nx][ny] == 0))
				flag = true;
		}
		else										//场景转换方面暂时没有想到更好的处理方法
		{
			if (PlayerState::player_position == "废弃的学校")
			{
				if (ny > 29)
				{
					PlayerState::player_position = "通往学校的路";
					std::string info = "你来到了" + PlayerState::player_position;
					Resource::Event_queue.push_back(info);
					ny = 0;
					flag = true;
				}
			}
			else if (PlayerState::player_position == "通往学校的路")
			{
				if (ny < 0)
				{
					PlayerState::player_position = "废弃的学校";
					std::string info = "你来到了" + PlayerState::player_position;
					Resource::Event_queue.push_back(info);
					ny = 29;
					flag = true;
				}
			}
		}

		//std::cout << nx << " " << ny << std::endl;

		if (flag)
		{
			PlayerState::player_x = nx;
			PlayerState::player_y = ny;
		}
	}
	
}

void updateWithoutInput()
{
	Resource::Maintime.add();

}

void draw_craft()
{
	putimage(0, 180, &Resource::craft_window);

	for (int i = 0; i < Resource::craft_map[UI::craft_name].size(); i++)
	{
		out_string(0 + 30, 180 + 30 + i * 30, Resource::craft_map[UI::craft_name][i]->product);

		if (i == UI::craft_pointer)
		{
			Resource::craft_map[UI::craft_name][i]->show();
		}
	}

	putimage(0, 180 + 23 + UI::craft_pointer * 30, &Resource::backpack_pointer);
}

void draw_backpack()
{
	putimage(BACKPACK_X, BACKPACK_Y, &Resource::backpack);
	
	out_number(BACKPACK_X + 240, BACKPACK_Y + 10, Resource::player_backpack.space);
	outtextxy(BACKPACK_X + 260, BACKPACK_Y + 10, _T("/"));
	out_number(BACKPACK_X + 270, BACKPACK_Y + 10, Resource::player_backpack.capacity);
	
	if (Resource::player_backpack.items.size() == 0)
		return;
	
	int now = 0;
	//从30， 60开始输出物品
	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
		out_string(BACKPACK_X + 30, BACKPACK_Y + 60 + now * 30, temp->name);
		out_number(BACKPACK_X + 300, BACKPACK_Y + 60 + now * 30, it->second);
		now++;
	}

	putimage(BACKPACK_X, BACKPACK_Y + 53 + UI::backpack_pointer * 30, &Resource::backpack_pointer);
}

/*
	画事件窗口
*/
void draw_eventWindow()
{
	putimage(180, 180, &Resource::eventWindow);

	std::string temp = "";

	int count = 0;
	int now = 0;

	for (int i = 0; i < UI::now_event.des.size(); i++)
	{
		if (UI::now_event.des[i] & 0x80)
		{
			count += 2;
			temp += UI::now_event.des[i];
			temp += UI::now_event.des[++i];
		}
		else
		{
			count += 1;
			temp += UI::now_event.des[i];
		}
		if (count >= 40)
		{
			count = 0;
			out_string(180 + 30, 180 + 20 + now * 25, temp);
			now++;
			temp = "";
		}
	}
	if (count != 0)
	{
		count = 0;
		out_string(180 + 30, 180 + 20 + now * 25, temp);
		now++;
		temp = "";
	}

	for (int i = 0; i < UI::now_event.selections.size(); i++)
	{
		if (i == UI::event_pointer)
			putimage(180, 180 + 50 + now * 25, &Resource::event_pointer);
		for (int j = 0; j < UI::now_event.selections[i]->des.size(); j++)
		{
			if (UI::now_event.selections[i]->des[j] & 0x80)
			{
				count += 2;
				temp += UI::now_event.selections[i]->des[j];
				temp += UI::now_event.selections[i]->des[++j];
			}
			else
			{
				count += 1;
				temp += UI::now_event.selections[i]->des[j];
			}
			if (count >= 40)
			{
				count = 0;
				out_string(180 + 30, 180 + 50 + now * 25, temp);
				now++;
				temp = "";
			}
		}
		if (count != 0)
		{
			count = 0;
			out_string(180 + 30, 180 + 50 + now * 25, temp);
			now++;
			temp = "";
		}
	}
}

/*
	180
*/
void draw_state()
{
	outtextxy(750, 30, _T("生命值:"));
	out_number(810, 30, PlayerState::player_hp);

	outtextxy(750, 60, _T("饥饿值:"));
	out_number(810, 60, PlayerState::player_food);

	outtextxy(750, 90, _T("口渴值:"));
	out_number(810, 90, PlayerState::player_water);

	outtextxy(750, 120, _T("神志:"));
	out_number(810, 120, PlayerState::player_sanity);

	outtextxy(750, 150, _T("疲劳值:"));
	out_number(810, 150, PlayerState::player_fatigue);

	outtextxy(750, 180, _T("您当前在:"));
	out_string(830, 180, PlayerState::player_position);

	outtextxy(750, 210, _T("您当前面向:"));
	if (PlayerState::player_face == 0)			//南方
	{
		outtextxy(850, 210, _T("南方"));
	}
	else if (PlayerState::player_face == 1)		//东方
	{
		outtextxy(850, 210, _T("东方"));
	}
	else if (PlayerState::player_face == 2)		//北方
	{
		outtextxy(850, 210, _T("北方"));
	}
	else if (PlayerState::player_face == 3)		//西方
	{
		outtextxy(850, 210, _T("西方"));
	}

	outtextxy(750, 240, _T("当前时间:"));
	std::string now_time = std::to_string(Resource::Maintime.days) + ":" + std::to_string(Resource::Maintime.hours) + ":";
	now_time += std::to_string(Resource::Maintime.minutes);
	out_string(830, 240, now_time);

}

/*
	事件最多20个字
*/
void draw_Event()
{
	if (Resource::Event_queue.empty())
		return;
	while (Resource::Event_queue.size() > 10)
		Resource::Event_queue.pop_front();

	int now = 0;
	for (std::list<Event>::iterator it = Resource::Event_queue.begin(); it != Resource::Event_queue.end(); it++)
	{
		out_string(750, 390 + now * 30, it->content);
		now++;
	}
}
void draw_itemBox()
{
	/*
		左边是 0， 180 右边是 360， 180
	*/
	putimage(0, 180, &Resource::itemBox);
	
	out_number(240, 180 + 10, Resource::player_backpack.space);
	outtextxy(260, 180 + 10, _T("/"));
	out_number(270, 180 + 10, Resource::player_backpack.capacity);

	out_number(360 + 240, 180 + 10, UI::now_itemBox.space);
	outtextxy(360 + 260, 180 + 10, _T("/"));
	out_number(360 + 270, 180 + 10, UI::now_itemBox.capacity);

	if (Resource::player_backpack.items.size() == 0 && UI::now_itemBox.items.size() == 0)
		return;

	int now = 0;

	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
		out_string( 30, 180 + 60 + now * 30, temp->name);
		out_number( 300, 180 + 60 + now * 30, it->second);
		now++;
	}

	now = 0;

	for (std::map<std::string, int>::iterator it = UI::now_itemBox.items.begin(); it != UI::now_itemBox.items.end(); it++)
	{
		Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
		out_string(30 + 360, 180 + 60 + now * 30, temp->name);
		out_number(300 + 360, 180 + 60 + now * 30, it->second);
		now++;
	}

	putimage(UI::itemBox_pointer.first * 360, 180 + 53 + UI::itemBox_pointer.second * 30, &Resource::backpack_pointer);

}

void draw()
{
	if (PlayerState::player_position == "废弃的学校")
	{
		putimage(0, 0, &Resource::school);
	}
	else if (PlayerState::player_position == "通往学校的路")
	{
		putimage(0, 0, &Resource::way_to_school);
	}
	
	transparentimage(NULL, PlayerState::player_x * BLOCK, PlayerState::player_y * BLOCK, &Resource::player);
	putimage(721, 0, &Resource::state);

	draw_placeable();
	draw_state();
	draw_Event();

	if (UI::open_window)
		draw_window();
	else if (UI::open_backpack)
		draw_backpack();
	if (UI::open_itemBox)
		draw_itemBox();
	if (UI::open_event)
		draw_eventWindow();
	if (UI::open_craft)
		draw_craft();
}

void init()
{
	Init::init_player_state();
	Init::init_image();
	Init::init_map();
	Init::init_item();
	Init::init_loot();
	Init::init_data();
}

int main()
{
	//调试用
	initgraph(1080, 720, EW_SHOWCONSOLE);

	//initgraph(1080, 720);

	//setaspectratio(1.5, 1.5);		//设置缩放因子

	init();
	BeginBatchDraw();
	while (1)
	{
		updateWithInput();
		updateWithoutInput();
		cleardevice();
		draw();
		FlushBatchDraw();
		Sleep(100);
	}
	EndBatchDraw();
	closegraph();			
	return 0;
}
