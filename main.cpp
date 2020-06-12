#define _CRT_SECURE_NO_WARNINGS
#define BACKPACK_X 180
#define BACKPACK_Y 180

/*
	b*[^:b#/]+.*$
	json����8115
*/

#include <easyx.h>			// ����ͼ�ο�ͷ�ļ�
#include <conio.h>
#include<string>
#include<cstring>
#include<iostream>
#include "head.h"
#pragma comment( lib, "MSIMG32.LIB")

std::string equip_order[6] = { "ͷ��", "����", "����", "Ь��", "����", "����" };

void out_number(int x, int y, int num)
{
	TCHAR s[10];
	_stprintf_s(s, _T("%d"), num);		// �߰汾 VC �Ƽ�ʹ�� _stprintf_s ����
	outtextxy(x, y, s);
}

void out_string(int x, int y, std::string str)
{
	char buff[100];
	strcpy_s(buff, str.c_str());
	outtextxy(x, y, buff);
}
/*
//		dstimg: Ŀ�� IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		x, y:	Ŀ����ͼλ��
//		srcimg: Դ IMAGE ����ָ�롣NULL ��ʾĬ�ϴ���
//		transparentcolor: ͸��ɫ��srcimg �ĸ���ɫ�����Ḵ�Ƶ� dstimg �ϣ��Ӷ�ʵ��͸����ͼ
*/

void transparentimage(IMAGE* dstimg, int x, int y, IMAGE* srcimg, UINT transparentcolor = 0)
{
	HDC dstDC = GetImageHDC(dstimg);
	HDC srcDC = GetImageHDC(srcimg);
	int w = srcimg->getwidth();
	int h = srcimg->getheight();

	// ʹ�� Windows GDI ����ʵ��͸��λͼ
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
		ս��״̬�²�����ʹ����Ʒ
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
				if (Resource::player_backpack.items.size() <= UI::backpack_pointer)		//�޸���һ��Сbug
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
			if (Resource::player_backpack.space + now->size <= Resource::player_backpack.capacity - now->capacity)	//�����±���
			{
				Resource::player_backpack.capacity -= now->capacity;
				PlayerState::bloat -= now->bloat;
				Resource::player_backpack.add(name);
				PlayerState::equip[equip_order[UI::equip_pointer]] = "";
			}
			else
			{
				info = "�ռ䲻��";
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
		info = "�ռ䲻��";
	}

	if (info != "")
	{
		Resource::Event_queue.push_back(info);
	}
}

/*
	�����ɽ�����Ʒ
*/
void interact()
{
	/*
		ս��״̬�²����Խ��н���
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

	if (interact_x >= 0 && interact_x <= 29 && interact_y >= 0 && interact_y <= 29)
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
	�ƶ���Ʒ
*/
void move_item()
{
	std::pair<int, int>now(0, 0);

	if (UI::itemBox_pointer == 0)			//�����ƶ�����Ʒ����
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

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//����Ʒ��Ϣ����
				
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
	else										//��Ʒ���ƶ�������
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

				UI::now_itemBox = Resource::itemBox_map[UI::interact_key];					//����Ʒ��Ϣ����

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
	���Ʒ�����Ʒ
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
	Ϊ���ڳ�ʼ��
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
		ͼƬ��70 130
	*/

	char buff[100];
	strcpy(buff, source.c_str());
	loadimage(&UI::now_window.img, buff);
	UI::now_window.des = des;
}

/*
	��ʾwindow
*/
void draw_window()
{
	putimage(180, 180, &Resource::Window);
	UI::now_window.show();
}


/*
	��ʾʱ�䴰��
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
			temp->hp -= PlayerState::attack_min;
			std::string info = "�������" + std::to_string(PlayerState::attack_min) + "���˺�";
			//transparentimage(NULL, interact_x, interact_y, &Resource::hit);
			Resource::Event_queue.push_back(info);
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
			if (UI::backpack_pointer.second - 1 >= 0 || UI::backpack_pointer.first >= 0)
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
			if (UI::equip_pointer + 1 < 6)	//ͷ�� ���� ���� Ь�� ���� ����
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
			UI::backpack_pointer = std::make_pair(0, 0);
		}
		else if (KEYDOWN('T'))
		{
			UI::open_craft = true;
			UI::craft_name = "player";
			UI::craft_pointer = 0;
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
		if (nx >= 0 && nx <= 29 && ny >= 0 && ny <= 29)			//�ƶ���Ϣ
		{
			if (Resource::mainMap[PlayerState::player_position][nx][ny] == 0)
				flag = true;
		}
		else										//����ת��������ʱû���뵽���õĴ�����
		{
			if (PlayerState::player_position == "������ѧУ")
			{
				if (ny > 29)
				{
					PlayerState::player_position = "ͨ��ѧУ��·";
					std::string info = "��������" + PlayerState::player_position;
					Resource::Event_queue.push_back(info);
					ny = 0;
					flag = true;
				}
			}
			else if (PlayerState::player_position == "ͨ��ѧУ��·")
			{
				if (ny < 0)
				{
					PlayerState::player_position = "������ѧУ";
					std::string info = "��������" + PlayerState::player_position;
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

/*
	���������Ľ�ʬ
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
			std::string info = "���ɱ��һֻ" + temp->name;
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
						int val = temp->attack();
						//transparentimage(NULL, PlayerState::player_x, PlayerState::player_y, &Resource::hit);
						std::string info = "���ܵ���" + std::to_string(val) + "���˺�";
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
		��������Ľ�ʬ
	*/
	
	if (Resource::zombie_map[PlayerState::player_position].size() > 20)
		clean_zombie();
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
	
	std::pair<int, int>now(0, 0);
	//��30�� 60��ʼ�����Ʒ
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
	���¼�����
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
	outtextxy(750, 30, _T("����ֵ:"));
	out_number(810, 30, PlayerState::player_hp);

	outtextxy(750, 60, _T("����ֵ:"));
	out_number(810, 60, PlayerState::player_food);

	outtextxy(750, 90, _T("�ڿ�ֵ:"));
	out_number(810, 90, PlayerState::player_water);

	outtextxy(750, 120, _T("��־:"));
	out_number(810, 120, PlayerState::player_sanity);

	outtextxy(750, 150, _T("ƣ��ֵ:"));
	out_number(810, 150, PlayerState::player_fatigue);

	outtextxy(750, 180, _T("����ǰ��:"));
	out_string(830, 180, PlayerState::player_position);

	outtextxy(750, 210, _T("����ǰ����:"));
	if (PlayerState::player_face == 0)			//�Ϸ�
	{
		outtextxy(850, 210, _T("�Ϸ�"));
	}
	else if (PlayerState::player_face == 1)		//����
	{
		outtextxy(850, 210, _T("����"));
	}
	else if (PlayerState::player_face == 2)		//����
	{
		outtextxy(850, 210, _T("����"));
	}
	else if (PlayerState::player_face == 3)		//����
	{
		outtextxy(850, 210, _T("����"));
	}

	outtextxy(750, 240, _T("��ǰʱ��:"));
	std::string now_time = std::to_string(Resource::Maintime.days) + ":" + std::to_string(Resource::Maintime.hours) + ":";
	now_time += std::to_string(Resource::Maintime.minutes);
	out_string(830, 240, now_time);

	/*
		����������
	*/
	rectangle(900, 30, 940, 130);
	//setfillcolor(GREEN);
	fillrectangle(900, 30, 940, 30 + PlayerState::step * 10);
	
	/*
		�Ƿ񱻷���
	*/
	std::string state;
	if (PlayerState::chased)state = "������";
	else state = "δ������";
	out_string(960, 30, state);
}
/*
	���Ƶ���
*/
void draw_zombie()
{
	for (int i = 0; i < Resource::zombie_map[PlayerState::player_position].size(); i++)
	{
		if(Resource::zombie_map[PlayerState::player_position][i]->alive)
			transparentimage(NULL, Resource::zombie_map[PlayerState::player_position][i]->x * BLOCK, Resource::zombie_map[PlayerState::player_position][i]->y * BLOCK, &Resource::zombie);
	}
}

/*
	�¼����20����
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
		����� 0�� 180 �ұ��� 360�� 180
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
			res = "[��]";
		out_string(180 + 35, 180 + 37 + i * 40, res);
	}

	putimage(180, 180 + 30 + UI::equip_pointer * 40, &Resource::backpack_pointer);

	std::string info = "";
	
	info = "��󹥻���" + std::to_string(PlayerState::attack_max);
	out_string(300 + 30, 180 + 30, info);

	info = "��С������" + std::to_string(PlayerState::attack_min);
	out_string(300 + 30, 180 + 30 + 40, info);

	info = "��ǰ�ٶ�" + std::to_string(PlayerState::speed);
	out_string(300 + 30, 180 + 30 + 80, info);

	info = "��׸��" + std::to_string(PlayerState::bloat);
	out_string(300 + 30, 180 + 30 + 120, info);

	info = "������" + std::to_string(PlayerState::defense);
	out_string(300 + 30, 180 + 30 + 160, info);
}

void draw()
{
	if (PlayerState::player_position == "������ѧУ")
	{
		putimage(0, 0, &Resource::school);
	}
	else if (PlayerState::player_position == "ͨ��ѧУ��·")
	{
		putimage(0, 0, &Resource::way_to_school);
	}
	
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

void init()
{
	Init::init_player_state();
	Init::init_image();
	Init::init_map();
	Init::init_item();
	Init::init_loot();
	Init::init_data();
	Init::init_easyx();
}

int main()
{
	//������
	initgraph(1080, 720, EW_SHOWCONSOLE);

	//initgraph(1080, 720);

	//setaspectratio(1.5, 1.5);		//������������

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
