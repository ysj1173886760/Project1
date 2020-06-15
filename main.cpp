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
#pragma comment( lib, "winmm.lib")

std::string equip_order[6] = { "头部", "上衣", "裤子", "鞋子", "背包", "武器" };
int walk_leg = 0;
bool extract = false;

int updateMinute = 2;
int leftMinute = 0;

void play_music_once(std::string str)
{
	char buff[100];
	std::string temp = "close " + str;
	strcpy_s(buff, temp.c_str());
	//std::cout << buff << std::endl;
	mciSendString(buff, NULL, 0, NULL);

	temp = "open Resources\\sound\\" + str + ".mp3 alias " + str;
	strcpy_s(buff, temp.c_str());
	//std::cout << buff << std::endl;
	mciSendString(buff, NULL, 0, NULL);

	temp = "play " + str;
	strcpy_s(buff, temp.c_str());
	//std::cout << buff << std::endl;
	mciSendString(buff, NULL, 0, NULL);
}

void out_number(int x, int y, int num)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), num);		// 高版本 VC 推荐使用 _stprintf_s 函数
	outtextxy(x, y, s);
}

void out_string(int x, int y, std::string str)
{
	char buff[50];
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

void update_backpack_pointer()
{
	if (UI::backpack_pointer.first * 10 + UI::backpack_pointer.second >= Resource::player_backpack.items.size())
	{
		if (UI::backpack_pointer.second - 1 >= 0 || UI::backpack_pointer.first > 0)
		{
			UI::backpack_pointer.second--;
			if (UI::backpack_pointer.second < 0)
			{
				UI::backpack_pointer.second += 10;
				UI::backpack_pointer.first--;
			}
		}
	}
}

void use_item()
{
	/*
		战斗状态下不可以使用物品
	*/
	if (PlayerState::chased)
		return;

	if (Resource::player_backpack.items.size() == 0)
		return;
	std::pair<int, int>now(0, 0);
	
	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		if (now == UI::backpack_pointer)
		{
			Item *temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			if (temp->can_use())
			{
				temp->use();
				Resource::player_backpack.remove(it->first);
				update_backpack_pointer();
				/*
				if (Resource::player_backpack.items.size() <= UI::backpack_pointer)		//修改了一个小bug
					UI::backpack_pointer = 0;
				*/
			}
			else if (temp->can_place())
			{
				if(temp->place())
					Resource::player_backpack.remove(it->first);
				update_backpack_pointer();
			}
			else if (temp->can_equip())
			{
				temp->equip();
				update_backpack_pointer();
			}
			return;
		}
		now.second++;
		if (now.second >= 10)
		{
			now.second -= 10;
			now.first++;
		}
	}
}

void unequip()
{
	std::string name = PlayerState::equip[equip_order[UI::equip_pointer]];
	if (name == "")
		return;
	std::string info = "";

	if (Resource::player_backpack.canPut(name))
	{
		Item* temp = Resource::item_map[Resource::item_map_for_string[name]];
		if (temp->is_cloth())
		{
			Cloth* now = (Cloth*)temp;
			PlayerState::bloat -= now->bloat;
			PlayerState::defense -= now->defense;
			Resource::player_backpack.add(name);
			PlayerState::equip[equip_order[UI::equip_pointer]] = "";
		}
		else if (temp->is_backpack())
		{
			Backpack* now = (Backpack*)temp;
			if (Resource::player_backpack.space + now->size <= Resource::player_backpack.capacity - now->capacity)	//能脱下背包
			{
				Resource::player_backpack.capacity -= now->capacity;
				PlayerState::bloat -= now->bloat;
				Resource::player_backpack.add(name);
				PlayerState::equip[equip_order[UI::equip_pointer]] = "";
			}
			else
			{
				info = "空间不足";
			}
		}
		else if (temp->is_weapon())
		{
			Weapon* now = (Weapon*)temp;
			PlayerState::attack_max -= now->attack_max;
			PlayerState::attack_min -= now->attack_min;
			Resource::player_backpack.add(name);
			PlayerState::equip[equip_order[UI::equip_pointer]] = "";
		}
	}
	else
	{
		info = "空间不足";
	}

	if (info != "")
	{
		Resource::Event_queue.push_back(info);
	}
}

/*
	操作可交互物品
*/
void interact()
{
	/*
		战斗状态下不可以进行交互
	*/
	if (PlayerState::chased)
		return;

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

	if (interact_x >= 0 && interact_x <= 29 && interact_y >= 0 && interact_y <= 29 && Resource::mainMap[PlayerState::player_position][interact_x][interact_y] >= 2)
	{
		Interaction* temp = NULL;

		temp = Resource::interaction_map[Resource::mainMap[PlayerState::player_position][interact_x][interact_y]];
		
		if (temp != NULL)
		{
			Interaction::TYPE type = temp->type;
			Resource::Event_queue.push_back(temp->des);

			if (type == Interaction::TYPE::ItemBox)
			{
				UI::now_itemBox = Resource::itemBox_map[temp->key];
				UI::interact_key = temp->key;
				UI::open_itemBox = true;
				UI::itemBox_pointer = 0;
				UI::itemBox_pointer_left = std::make_pair(0, 0);
				UI::itemBox_pointer_right = std::make_pair(0, 0);
				play_music_once("itembox_open");
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
	std::pair<int, int>now(0, 0);

	if (UI::itemBox_pointer == 0)			//背包移动到物品箱中
	{
		for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
		{
			if (now == UI::itemBox_pointer_left)
			{
				if (Resource::itemBox_map[UI::interact_key].canPut(it->first))
				{
					Resource::itemBox_map[UI::interact_key].add(it->first);
					Resource::player_backpack.remove(it->first);
				}

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//把物品信息更新
				
				if (UI::itemBox_pointer_left.first * 10 + UI::itemBox_pointer_left.second >= Resource::player_backpack.items.size())
				{
					if (UI::itemBox_pointer_left.second - 1 >= 0 || UI::itemBox_pointer_left.first > 0)
					{
						UI::itemBox_pointer_left.second--;
						if (UI::itemBox_pointer_left.second < 0)
						{
							UI::itemBox_pointer_left.second += 10;
							UI::itemBox_pointer_left.first--;
						}
					}
				}
				return;
			}
			now.second++;
			if (now.second >= 10)
			{
				now.first++;
				now.second -= 10;
			}
		}
	}
	else										//物品箱移动到背包
	{
		for (std::map<std::string, int>::iterator it = UI::now_itemBox.items.begin(); it != UI::now_itemBox.items.end(); it++)
		{
			if (now == UI::itemBox_pointer_right)
			{
				if (Resource::player_backpack.canPut(it->first))
				{
					Resource::player_backpack.add(it->first);
					Resource::itemBox_map[UI::interact_key].remove(it->first);
				}

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//把物品信息更新

				if (UI::itemBox_pointer_right.first * 10 + UI::itemBox_pointer_right.second >= UI::now_itemBox.items.size())
				{
					if (UI::itemBox_pointer_right.second - 1 >= 0 || UI::itemBox_pointer_right.first > 0)
					{
						UI::itemBox_pointer_right.second--;
						if (UI::itemBox_pointer_right.second < 0)
						{
							UI::itemBox_pointer_right.second += 10;
							UI::itemBox_pointer_right.first--;
						}
					}
				}
				return;
			}
			now.second++;
			if (now.second >= 10)
			{
				now.first++;
				now.second -= 10;
			}
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
	std::pair<int, int> now(0, 0);
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
		now.second++;
		if (now.second >= 10)
		{
			now.second -= 10;
			now.first++;
		}
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
			else if (UI::now_event.selections[i]->type == Result::TYPE::Break)
			{
				UI::now_event.selections[i]->do_result();
			}
			else if (UI::now_event.selections[i]->type == Result::TYPE::ChangePos)
			{
				play_music_once("open_door");
				UI::now_event.selections[i]->do_result();
			}
			else if (UI::now_event.selections[i]->type == Result::TYPE::Extract)
			{
				if (Resource::player_backpack.have("通行证"))
				{
					extract = true;
				}
				else
				{
					std::string info = "你没有权限";
					Resource::Event_queue.push_back(info);
				}
			}
			else if (UI::now_event.selections[i]->type == Result::TYPE::DoNothing)
			{
				//just do nothing
			}
			
			return;
		}
	}
}

void attack()
{
	if (PlayerState::step != PlayerState::speed)
		return;

	PlayerState::step = 0;

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
		Enemy* temp = NULL;

		if (Resource::mainMap[PlayerState::player_position][interact_x][interact_y] < 0)
		{
			temp = Resource::zombie_map[PlayerState::player_position][-1 - Resource::mainMap[PlayerState::player_position][interact_x][interact_y]];
		}
		
		if (temp != NULL)
		{
			play_music_once("player_attack");
			int hit = Resource::myrandom.getRandom(1, 100);
			if (hit >= 1 && hit <= (100 - PlayerState::bloat * 3))
			{
				int dmg = Resource::myrandom.getRandom(PlayerState::attack_min, PlayerState::attack_max);
				temp->hp -= dmg;
				std::string info = "你造成了" + std::to_string(dmg) + "点伤害";
				//transparentimage(NULL, interact_x, interact_y, &Resource::hit);
				Resource::Event_queue.push_back(info);
			}
			else
			{
				std::string info = "你未命中敌人";
				Resource::Event_queue.push_back(info);
			}
		}
	}
}

void craft()
{
	Resource::craft_map[UI::craft_name][UI::craft_pointer.first * 10 + UI::craft_pointer.second ]->craft_item();
}

int getInt(std::string s)
{
	if (s.size() == 2)
	{
		return s[1] - '0';
	}
	else if (s.size() == 3)
	{
		return (s[1] - '0') * 10 + s[2] - '0';
	}
	else return 0;
}
std::string getUpMap()
{
	std::string temp = PlayerState::player_position;
	temp[0]--;
	return temp;
}

std::string getDownMap()
{
	std::string temp = PlayerState::player_position;
	temp[0]++;
	return temp;
}

std::string getLeftMap()
{
	std::string temp = "A";
	temp[0] = PlayerState::player_position[0];
	int now = getInt(PlayerState::player_position);
	now--;
	temp += std::to_string(now);
	return temp;
}

std::string getRightMap()
{
	std::string temp = "A";
	temp[0] = PlayerState::player_position[0];
	int now = getInt(PlayerState::player_position);
	now++;
	temp += std::to_string(now);
	return temp;
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
			if (UI::backpack_pointer.second - 1 >= 0 || UI::backpack_pointer.first > 0)
			{
				UI::backpack_pointer.second--;
				if (UI::backpack_pointer.second < 0)
				{
					UI::backpack_pointer.second += 10;
					UI::backpack_pointer.first--;
				}
			}
		}
		else if (KEYDOWN('S'))
		{
			if (UI::backpack_pointer.first * 10 + UI::backpack_pointer.second + 1 < int(Resource::player_backpack.items.size()))
			{
				UI::backpack_pointer.second++;
				if (UI::backpack_pointer.second >= 10)
				{
					UI::backpack_pointer.first++;
					UI::backpack_pointer.second -= 10;
				}
			}
		}
		else if (KEYDOWN('F'))
		{
			use_item();
		}
		else if (KEYDOWN('E') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_backpack = false;
			UI::backpack_pointer = std::make_pair(0, 0);
			play_music_once("close_backpack");
		}
		else if (KEYDOWN('X'))
		{
			UI::open_window = true;
			initWindow();
		}
	}
	else if (UI::open_equip)
	{
		if (KEYDOWN('W'))
		{
			if (UI::equip_pointer - 1 >= 0)
				UI::equip_pointer--;
		}
		else if (KEYDOWN('S'))
		{				
			if (UI::equip_pointer + 1 < 6)	//头部 上衣 裤子 鞋子 背包 武器
				UI::equip_pointer++;
		}
		else if (KEYDOWN('I') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_equip = false;
		}
		else if (KEYDOWN('F'))
		{
			unequip();
		}
	}
	else if(UI::open_itemBox)
	{
		if (KEYDOWN('W'))
		{
			if (UI::itemBox_pointer == 0)
			{
				if (UI::itemBox_pointer_left.second - 1 >= 0 || UI::itemBox_pointer_left.first > 0)
				{
					UI::itemBox_pointer_left.second--;
					if (UI::itemBox_pointer_left.second < 0)
					{
						UI::itemBox_pointer_left.second += 10;
						UI::itemBox_pointer_left.first--;
					}
				}
			}
			else
			{
				if (UI::itemBox_pointer_right.second - 1 >= 0 || UI::itemBox_pointer_right.first > 0)
				{
					UI::itemBox_pointer_right.second--;
					if (UI::itemBox_pointer_right.second < 0)
					{
						UI::itemBox_pointer_right.second += 10;
						UI::itemBox_pointer_right.first--;
					}
				}
			}
		}
		else if (KEYDOWN('S'))
		{
			if (UI::itemBox_pointer == 0)
			{
				if (UI::itemBox_pointer_left.first * 10 + UI::itemBox_pointer_left.second + 1 < int(Resource::player_backpack.items.size()))
				{
					UI::itemBox_pointer_left.second++;
					if (UI::itemBox_pointer_left.second >= 10)
					{
						UI::itemBox_pointer_left.first++;
						UI::itemBox_pointer_left.second -= 10;
					}
				}
			}
			else
			{	
				//std::cout << UI::itemBox_pointer_right.first << " " << UI::itemBox_pointer_right.second << std::endl;
				if (UI::itemBox_pointer_right.first * 10 + UI::itemBox_pointer_right.second + 1 < int(UI::now_itemBox.items.size()))
				{
					UI::itemBox_pointer_right.second++;
					if (UI::itemBox_pointer_right.second >= 10)
					{
						UI::itemBox_pointer_right.first++;
						UI::itemBox_pointer_right.second -= 10;
					}
				}
			}
				
		}
		else if (KEYDOWN('D'))
		{
			if (UI::itemBox_pointer == 0)
				UI::itemBox_pointer = 1;
		}
		else if (KEYDOWN('A'))
		{
			if (UI::itemBox_pointer == 1)
				UI::itemBox_pointer = 0;
		}
		else if (KEYDOWN('E') || KEYDOWN(VK_ESCAPE))
		{
			UI::open_itemBox = false;
			play_music_once("itembox_close");
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
			if (UI::craft_pointer.second - 1 >= 0 || UI::craft_pointer.first > 0)
			{
				UI::craft_pointer.second--;
				if (UI::craft_pointer.second < 0)
				{
					UI::craft_pointer.second += 10;
					UI::craft_pointer.first--;
				}
			}
		}
		else if (KEYDOWN('S'))
		{
			if (UI::craft_pointer.first * 10 + UI::craft_pointer.second + 1 < int(Resource::craft_map[UI::craft_name].size()))
			{
				UI::craft_pointer.second++;
				if (UI::craft_pointer.second >= 10)
				{
					UI::craft_pointer.first++;
					UI::craft_pointer.second -= 10;
				}
			}
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
		bool can_move = false;
		bool need_move = false;

		if (KEYDOWN('A'))
		{
			nx--;
			PlayerState::player_face = 1;
			need_move = true;
		}
		else if (KEYDOWN('D'))
		{
			nx++;
			PlayerState::player_face = 3;
			need_move = true;
		}
		else if (KEYDOWN('W'))
		{
			ny--;
			PlayerState::player_face = 2;
			need_move = true;
		}
		else if (KEYDOWN('S'))
		{
			ny++;
			PlayerState::player_face = 0;
			need_move = true;
		}
		else if (KEYDOWN('F'))
		{
			interact();
		}
		else if (KEYDOWN('E'))
		{
			play_music_once("open_backpack");
			UI::open_backpack = true;
			UI::backpack_pointer = std::make_pair(0, 0);
		}
		else if (KEYDOWN('T'))
		{
			UI::open_craft = true;
			UI::craft_name = "player";
			UI::craft_pointer = std::make_pair(0, 0);
		}
		else if (KEYDOWN('J'))
		{
			attack();
		}
		else if (KEYDOWN('I'))
		{
			UI::open_equip = true;
			UI::equip_pointer = 0;
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
		if (need_move)
		{
			if (nx >= 0 && nx <= 29 && ny >= 0 && ny <= 29)			//移动信息
			{
				if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
					can_move = true;
			}
			else										//场景转换方面暂时没有想到更好的处理方法
			{
				if (ny > 29)			//下
				{
					std::string newPos = getDownMap();
					if (Resource::mainMap[newPos][nx][0] == 0)
					{
						PlayerState::player_position = newPos;
						std::string info = "你来到了" + PlayerState::player_position;
						Resource::Event_queue.push_back(info);
						ny = 0;
						can_move = true;
					}
				}
				else if (ny < 0)		//上
				{
					std::string newPos = getUpMap();
					if (Resource::mainMap[newPos][nx][29] == 0)
					{
						PlayerState::player_position = newPos;
						std::string info = "你来到了" + PlayerState::player_position;
						Resource::Event_queue.push_back(info);
						ny = 29;
						can_move = true;
					}
				}
				else if (nx < 0)		//左
				{
					std::string newPos = getLeftMap();
					if (Resource::mainMap[newPos][29][ny] == 0)
					{
						PlayerState::player_position = newPos;
						std::string info = "你来到了" + PlayerState::player_position;
						Resource::Event_queue.push_back(info);
						nx = 29;
						can_move = true;
					}
				}
				else if (nx > 29)		//右
				{
					std::string newPos = getRightMap();
					if (Resource::mainMap[newPos][0][ny] == 0)
					{
						PlayerState::player_position = newPos;
						std::string info = "你来到了" + PlayerState::player_position;
						Resource::Event_queue.push_back(info);
						nx = 0;
						can_move = true;
					}
				}
			}
		}
		

		//std::cout << nx << " " << ny << std::endl;

		if (can_move)
		{
			if (walk_leg == 0)play_music_once("player_walk0");
			else play_music_once("player_walk1");
			walk_leg ^= 1;
			PlayerState::player_x = nx;
			PlayerState::player_y = ny;
		}
	}
	
}

/*
	清理死亡的僵尸
*/
void clean_zombie()
{
	//std::cout << Resource::zombie_map[PlayerState::player_position].size() << std::endl;
	for (std::vector<Enemy*>::iterator it = Resource::zombie_map[PlayerState::player_position].begin(); it != Resource::zombie_map[PlayerState::player_position].end();)
	{
		Enemy* temp = *it;
		if (!temp->alive)
		{
			it = Resource::zombie_map[PlayerState::player_position].erase(it);
		}
		else it++;
	}
	int now = 0;
	for (std::vector<Enemy*>::iterator it = Resource::zombie_map[PlayerState::player_position].begin(); it != Resource::zombie_map[PlayerState::player_position].end(); it++)
	{
		Enemy* temp = *it;
		temp->id = -1 - now;
		Resource::mainMap[PlayerState::player_position][temp->x][temp->y] = temp->id;
		now++;
	}
}

void updateWithoutInput()
{
	/*
		update time
	*/
	Resource::Maintime.add();

	/*
		update player
	*/

	if (PlayerState::step < PlayerState::speed)
	{
		PlayerState::step++;
	}

	leftMinute += Resource::Maintime.getPastTime();
	while (leftMinute > updateMinute)
	{
		leftMinute -= updateMinute;
		PlayerState::player_food--;
		PlayerState::player_water--;
		PlayerState::player_fatigue++;
		if (PlayerState::player_food < 20)
		{
			PlayerState::player_hp--;
		}
		if (PlayerState::player_water < 30)
		{
			PlayerState::player_hp--;
		}
		if (PlayerState::player_fatigue > 80)
		{
			PlayerState::player_hp--;
		}
		if (PlayerState::player_food > 100)PlayerState::player_food = 100;
		if (PlayerState::player_water > 100)PlayerState::player_water = 100;
		if (PlayerState::player_fatigue < 0)PlayerState::player_fatigue = 0;
		if (PlayerState::player_food < 0)PlayerState::player_food = 0;
		if (PlayerState::player_water < 0)PlayerState::player_water = 0;
		if (PlayerState::player_fatigue > 100)PlayerState::player_fatigue = 100;
		if (PlayerState::player_hp > 100)PlayerState::player_hp = 100;
	}
	
	/*
		update zombie
	*/
	bool flag = false;

	for (std::vector<Enemy*>::iterator it = Resource::zombie_map[PlayerState::player_position].begin(); it != Resource::zombie_map[PlayerState::player_position].end(); it++)
	{
		Enemy* temp = *it;

		if (!temp->alive)
			continue;
		if (temp->hp <= 0)
		{
			play_music_once("zombie_death");
			if(temp->type == Enemy::TYPE::boss)
				Resource::player_backpack.add("通行证");
			std::string info = "你击杀了一只" + temp->name;
			PlayerState::kill_zombie++;
			Resource::Event_queue.push_back(info);
			Resource::mainMap[PlayerState::player_position][temp->x][temp->y] = 0;
			temp->alive = false;
			//it = Resource::zombie_map[PlayerState::player_position].erase(it);
		}
		else
		{
			if (temp->chaseing())
			{
				flag = true;
				if (temp->add_step())
				{
					if (temp->can_attack())
					{
						if (temp->is_boss())
							play_music_once("boss_attack");
						else
							play_music_once("zombie_attack");
						int val = temp->attack();
						//transparentimage(NULL, PlayerState::player_x, PlayerState::player_y, &Resource::hit);
						std::string info = "你受到了" + std::to_string(val) + "点伤害";
						Resource::Event_queue.push_back(info);
					}
					else
						temp->move();
				}
			}
		}
	}

	PlayerState::chased = flag;

	/*
		清除死亡的僵尸
	*/
	
	if (Resource::zombie_map[PlayerState::player_position].size() > 20)
		clean_zombie();

	/*
		spawn_zombie
	*/
	int code = Resource::myrandom.getRandom(1, 100);
	if (code >= 10 && code <= 15)
	{
		Init::spawn_zombie(true);
	}
}

void draw_craft()
{
	putimage(0, 180, &Resource::craft_window);

	std::pair<int, int>now(0, 0);

	for (int i = 0; i < Resource::craft_map[UI::craft_name].size(); i++)
	{
		if (now.first == UI::craft_pointer.first)
		{
			out_string(0 + 30, 180 + 30 + now.second * 30, Resource::craft_map[UI::craft_name][i]->product);
		}
		if (now == UI::craft_pointer)
		{
			Resource::craft_map[UI::craft_name][i]->show();
		}
		now.second++;
		if (now.second == 10)
		{
			now.second -= 10;
			now.first++;
		}
	}

	putimage(0, 180 + 23 + UI::craft_pointer.second * 30, &Resource::backpack_pointer);
}

void draw_backpack()
{
	putimage(BACKPACK_X, BACKPACK_Y, &Resource::backpack);
	
	out_number(BACKPACK_X + 240, BACKPACK_Y + 10, Resource::player_backpack.space);
	outtextxy(BACKPACK_X + 260, BACKPACK_Y + 10, _T("/"));
	out_number(BACKPACK_X + 270, BACKPACK_Y + 10, Resource::player_backpack.capacity);
	
	if (Resource::player_backpack.items.size() == 0)
		return;
	
	std::pair<int, int>now(0, 0);
	//从30， 60开始输出物品
	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		if (now.first == UI::backpack_pointer.first)
		{
			Item* temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			out_string(BACKPACK_X + 30, BACKPACK_Y + 60 + now.second * 30, temp->name);
			out_number(BACKPACK_X + 300, BACKPACK_Y + 60 + now.second * 30, it->second);
		}
		now.second++;
		if (now.second == 10)
		{
			now.second = 0;
			now.first++;
		}
	}

	putimage(BACKPACK_X, BACKPACK_Y + 53 + UI::backpack_pointer.second * 30, &Resource::backpack_pointer);
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

	/*
		绘制体力条
	*/
	rectangle(900, 30, 940, 130);
	//setfillcolor(GREEN);
	fillrectangle(900, 30, 940, 30 + PlayerState::step * 10);
	
	/*
		是否被发现
	*/
	std::string state;
	if (PlayerState::chased)state = "被发现";
	else state = "未被发现";
	out_string(960, 30, state);
}
/*
	绘制敌人
*/
void draw_zombie()
{
	for (int i = 0; i < Resource::zombie_map[PlayerState::player_position].size(); i++)
	{
		if (Resource::zombie_map[PlayerState::player_position][i]->alive)
		{
			if (Resource::zombie_map[PlayerState::player_position][i]->type == Enemy::TYPE::zombie)
				transparentimage(NULL, Resource::zombie_map[PlayerState::player_position][i]->x * BLOCK, Resource::zombie_map[PlayerState::player_position][i]->y * BLOCK, &Resource::zombie);
			else if (Resource::zombie_map[PlayerState::player_position][i]->type == Enemy::TYPE::hunter)
				transparentimage(NULL, Resource::zombie_map[PlayerState::player_position][i]->x * BLOCK, Resource::zombie_map[PlayerState::player_position][i]->y * BLOCK, &Resource::hunter);
			else if (Resource::zombie_map[PlayerState::player_position][i]->type == Enemy::TYPE::tyrant)
				transparentimage(NULL, Resource::zombie_map[PlayerState::player_position][i]->x * BLOCK, Resource::zombie_map[PlayerState::player_position][i]->y * BLOCK, &Resource::tyrant);
			else if (Resource::zombie_map[PlayerState::player_position][i]->type == Enemy::TYPE::boss)
				transparentimage(NULL, Resource::zombie_map[PlayerState::player_position][i]->x * BLOCK, Resource::zombie_map[PlayerState::player_position][i]->y * BLOCK, &Resource::boss);
		}
	}
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

	std::pair<int, int>now;

	for (std::map<std::string, int>::iterator it = Resource::player_backpack.items.begin(); it != Resource::player_backpack.items.end(); it++)
	{
		if (now.first == UI::itemBox_pointer_left.first)
		{
			Item* temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			out_string(30, 180 + 60 + now.second * 30, temp->name);
			out_number(300, 180 + 60 + now.second * 30, it->second);
		}
		now.second++;
		if (now.second == 10)
		{
			now.second = 0;
			now.first++;
		}
	}

	now = std::make_pair(0, 0);

	for (std::map<std::string, int>::iterator it = UI::now_itemBox.items.begin(); it != UI::now_itemBox.items.end(); it++)
	{
		if (now.first == UI::itemBox_pointer_right.first)
		{
			Item* temp = Resource::item_map[Resource::item_map_for_string[it->first]];
			out_string(30 + 360, 180 + 60 + now.second * 30, temp->name);
			out_number(300 + 360, 180 + 60 + now.second * 30, it->second);
		}
		now.second++;
		if (now.second == 10)
		{
			now.second = 0;
			now.first++;
		}
	}
	if (UI::itemBox_pointer == 0)
	{
		putimage(0, 180 + 53 + UI::itemBox_pointer_left.second * 30, &Resource::backpack_pointer);
	}
	else
	{
		putimage(360, 180 + 53 + UI::itemBox_pointer_right.second * 30, &Resource::backpack_pointer);
	}

}


void draw_equip()
{
	putimage(180, 180, &Resource::equip);

	for (int i = 0; i < 6; i++)
	{
		std::string res = PlayerState::equip[equip_order[i]];
		if (res == "")
			res = "[空]";
		out_string(180 + 35, 180 + 37 + i * 40, res);
	}

	putimage(180, 180 + 30 + UI::equip_pointer * 40, &Resource::backpack_pointer);

	std::string info = "";
	
	info = "最大攻击力" + std::to_string(PlayerState::attack_max);
	out_string(400 + 30, 180 + 37, info);

	info = "最小攻击力" + std::to_string(PlayerState::attack_min);
	out_string(400 + 30, 180 + 37 + 40, info);

	info = "当前速度" + std::to_string(PlayerState::speed);
	out_string(400 + 30, 180 + 37 + 80, info);

	info = "累赘度" + std::to_string(PlayerState::bloat);
	out_string(400 + 30, 180 + 37 + 120, info);

	info = "防御力" + std::to_string(PlayerState::defense);
	out_string(400 + 30, 180 + 37 + 160, info);
}

void draw()
{
	putimage(0, 0, &Resource::map_image[PlayerState::player_position]);
	
	transparentimage(NULL, PlayerState::player_x * BLOCK, PlayerState::player_y * BLOCK, &Resource::player);
	putimage(721, 0, &Resource::state);

	draw_placeable();
	draw_state();
	draw_Event();
	draw_zombie();

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
	if (UI::open_equip)
		draw_equip();
}

char Input()
{
	char c = 0;

	if (_kbhit())
	{
		c = _getch();
	}
	return c;
}

void init()
{
	Init::init_item();
	Init::init_image();
	Init::init_easyx();
}

void init_playerData()
{
	try
	{
		std::fstream file;
		file.open("data\\playerdata.in", std::ios::in);
		file >> PlayerState::experience;
		file.close();
		std::cout << "player init complete:"<<PlayerState::experience << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << " " << e.what() << std::endl;
	}
}

void init_newgame()
{
	leftMinute = 0;
	extract = false;
	mciSendString("close bgm", NULL, 0, NULL);
	play_music_once("game_init");
	cleardevice();
	putimage(0, 0, &Resource::loaddata);
	FlushBatchDraw();
	init_playerData();
	Init::init_map();
	Init::init_data();
	Init::init_player_state();
	Init::init_loot();
	Init::spawn_zombie(false);
	UI::open_backpack = false;
	UI::open_craft = false;
	UI::open_equip = false;
	UI::open_event = false;
	UI::open_itemBox = false;
	UI::open_window = false;

	int x = Resource::myrandom.getRandom(1, 28);
	int y = Resource::myrandom.getRandom(1, 28);
	while (Resource::mainMap["F6"][x][y] != 0)
	{
		x = Resource::myrandom.getRandom(1, 28);
		y = Resource::myrandom.getRandom(1, 28);
	}
	Init::create_zombie(x, y, "F6", "boss");

	LOGFONT default_style;
	gettextstyle(&default_style);
	settextcolor(RED);
	settextstyle(30, 30, _T("华康方圆体W7"));
	clock_t previous = clock();
	clock_t now;
	int need_to_go = 10000;
	while (1)
	{
		now = clock();
		need_to_go -= (now - previous);
		previous = clock();
		if (need_to_go <= 0)
			break;
		cleardevice();
		putimage(0, 0, &Resource::deploy);
		std::string temp = std::to_string(need_to_go / 1000) + ":" + std::to_string(need_to_go % 1000);
		out_string(450, 370, temp);
		FlushBatchDraw();
	}
	settextstyle(&default_style);
	settextcolor(WHITE);
	Resource::Maintime.set(8, 0, 0, 0);
	mciSendString("close game_init", NULL, 0, NULL);
	mciSendString("open Resources\\sound\\bg1.mp3 alias game", NULL, 0, NULL);
	mciSendString("play game repeat", NULL, 0, NULL);
}

std::string GetExePath(void)
{
	char szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileNameA(NULL, szFilePath, MAX_PATH);
	//(strrchr(szFilePath, '\\'))[0] = 0; // 删除文件名，只获得路径字串
	std::string path = szFilePath;

	return path;
}

void settlement()
{
	Sleep(2000);
	mciSendString("close game", NULL, 0, NULL);
	mciSendString("open Resources\\sound\\game_over.mp3 alias game_over", NULL, 0, NULL);
	mciSendString("play game_over", NULL, 0, NULL);
	putimage(0, 0, &Resource::death_page);
	FlushBatchDraw();
	//Sleep(5000);
	while (1)
	{
		if(KEYDOWN(VK_SPACE))break;
		Sleep(16);
	}
	
}

void success()
{
	mciSendString("close game", NULL, 0, NULL);
	mciSendString("open Resources\\sound\\game_success.mp3 alias game_success", NULL, 0, NULL);
	mciSendString("play game_success", NULL, 0, NULL);
	putimage(0, 0, &Resource::success);
	FlushBatchDraw();
	//Sleep(5000);
	while (1)
	{
		if (KEYDOWN(VK_SPACE))break;
		Sleep(16);
	}
	
}

void save_playerData()
{
	try
	{
		std::fstream file;
		file.open("data\\playerdata.in", std::ios::out | std::ios::trunc);
		file << PlayerState::experience;
		file.close();
		std::cout << "player save complete" << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << " " << e.what() << std::endl;
	}
}

void success_add_experience()
{
	int temp = PlayerState::experience;
	PlayerState::experience += PlayerState::kill_zombie * 2;

	LOGFONT default_style;
	gettextstyle(&default_style);
	settextcolor(RED);
	settextstyle(30, 30, _T("华康方圆体W7"));
	setfillcolor(WHITE);
	while (1)
	{
		double percentage = double(temp % 100) / 100.0;
		if (temp < PlayerState::experience)temp++;
		int level = temp / 100;
		std::string info = "LV:" + std::to_string(level);
		if (KEYDOWN(VK_RETURN))break;
		cleardevice();
		putimage(0, 0, &Resource::settlement);
		rectangle(185, 140, 785, 200);
		fillrectangle(185, 140, 185 + int(percentage * 600.0), 200);
		out_string(810, 150, info);
		out_number(410, 280, temp);
		FlushBatchDraw();
		Sleep(30);
	}
	settextstyle(&default_style);
	settextcolor(WHITE);
	setfillcolor(GREEN);
	save_playerData();
	mciSendString("close game_success", NULL, 0, NULL);
}

void fail_add_experience()
{
	int temp = PlayerState::experience;
	PlayerState::experience += PlayerState::kill_zombie;

	LOGFONT default_style;
	gettextstyle(&default_style);
	settextcolor(RED);
	settextstyle(30, 30, _T("华康方圆体W7"));
	setfillcolor(WHITE);
	while (1)
	{
		double percentage = double(temp % 100) / 100.0;
		if (temp < PlayerState::experience)temp++;
		int level = temp / 100;
		std::string info = "LV:" + std::to_string(level);
		if (KEYDOWN(VK_RETURN))break;
		cleardevice();
		putimage(0, 0, &Resource::settlement);
		rectangle(185, 140, 785, 200);
		fillrectangle(185, 140, 185 + int(percentage * 600.0), 200);
		out_string(810, 150, info);
		out_number(410, 280, temp);
		FlushBatchDraw();
		Sleep(30);
	}
	settextstyle(&default_style);
	settextcolor(WHITE);
	setfillcolor(GREEN);
	save_playerData();
	mciSendString("close game_over", NULL, 0, NULL);
}

/*
	main game
*/

void do_game()
{
	while (1)
	{
		updateWithInput();
		updateWithoutInput();
		if (PlayerState::player_hp <= 0)
		{
			play_music_once("player_death");
			settlement();
			fail_add_experience();
			break;
		}
		if (extract)
		{
			success();
			success_add_experience();
			break;
		}
		cleardevice();
		draw();
		FlushBatchDraw();
		Sleep(100);
	}
}





int main()
{
	//调试用
	//initgraph(1080, 720, EW_SHOWCONSOLE);

	initgraph(1080, 720);

	//setaspectratio(1.5, 1.5);		//设置缩放因子

	init();

	mciSendString("open Resources\\sound\\bg2.mp3 alias bgm", NULL, 0, NULL);
	mciSendString("open Resources\\sound\\menu_move.mp3 alias move", NULL, 0, NULL);
	mciSendString("play bgm repeat", NULL, 0, NULL);
	//std::cout << GetExePath() << std::endl;

	int main_pointer = 0;
	bool newGame = false;
	bool showHelp = false;
	bool showSetting = false;
	bool keydown_w = false;
	bool keydown_s = false;
	/*
	char volume;
	mciSendString("status movie volume", &volume, sizeof(volume), 0);
	*/

	BeginBatchDraw();
	while (1)
	{
		if (KEYDOWN('W'))
		{
			keydown_w = true;
		}
		if (KEYDOWN('S'))
		{
			keydown_s = true;
		}
		if (KEYUP('W'))
		{
			if (keydown_w)
			{
				keydown_w = false;
				if (main_pointer != 0)
				{
					main_pointer--;
					play_music_once("menu_move");
					//mciSendString("close move", NULL, 0, NULL);
					//mciSendString("open Resources\\sound\\menu_move.mp3 alias move", NULL, 0, NULL);
					//mciSendString("play move", NULL, 0, NULL);
				}
			}
		}
		if (KEYUP('S'))
		{
			if (keydown_s)
			{
				keydown_s = false;
				if (main_pointer != 2)
				{
					main_pointer++;
					play_music_once("menu_move");
					//mciSendString("close move", NULL, 0, NULL);
					//mciSendString("open Resources\\sound\\menu_move.mp3 alias move", NULL, 0, NULL);
					//mciSendString("play move", NULL, 0, NULL);
				}
			}
		}
		if (KEYDOWN(VK_SPACE))
		{
			if (main_pointer == 0 && showHelp == false)
			{
				newGame = true;
			}
			else if (main_pointer == 1)
			{
				showHelp = true;
			}
			else if (main_pointer == 2)
			{
				showSetting = true;
			}
		}
		else if (KEYDOWN(VK_ESCAPE))
		{
			showHelp = false;
			showSetting = false;
		}
		cleardevice();
		putimage(0, 0, &Resource::main);
		putimage(425, 470, &Resource::begin);
		putimage(450, 550, &Resource::help);
		putimage(434, 630, &Resource::setting);
		putimage(300, 470 + main_pointer * 80 , &Resource::main_pointer);
		if (showHelp)
		{
			putimage(270, 140, &Resource::help_page);
		}
		if (showSetting)
		{
			//50 160
			putimage(270, 140, &Resource::setting_page);

		}
		FlushBatchDraw();
		if (newGame)
		{
			init_newgame();
			do_game();
			newGame = false;
			mciSendString("open Resources\\sound\\bg2.mp3 alias bgm", NULL, 0, NULL);
			mciSendString("play bgm repeat", NULL, 0, NULL);
			main_pointer = 0;
			newGame = false;
			showHelp = false;
			keydown_w = false;
			keydown_s = false;
		}
		
		Sleep(16);		//60fps
	}
	
	EndBatchDraw();
	closegraph();			
	return 0;
}
