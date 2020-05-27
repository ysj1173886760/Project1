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
	PlayerState::player_position = "������ѧУ";
	PlayerState::player_face = 0;
	PlayerState::player_sanity = 100;
}

/*
	0�ǿ���ͨ����
	1���ϰ�
	2 �� 2147483647 �� �ɽ�����Ʒ
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
	Resource::item_map.push_back(Item(1, 0, 0, 5, 0, 0, 1, 1, "ƻ��", "����ɿڵ�ƻ������ţ����ĳ�ֹ�ϵ", "����˸�ƻ�����о�������"));
	Resource::item_map.push_back(Item(1, 1, 0, 0, 5, 0, 1, 1, "��Ȫˮ", "һƿ��ͨ�Ŀ�Ȫˮ��������Դ�ѷ���ĩ���Ե��쳣����", "�����ƿˮ���ڿʳ̶���������"));
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
		2��������Ͱ  0������
	*/
	Resource::school_map[28][19] = 2;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0, "������ʹ����ס�̱ǵ�ζ�����˷��������Ͱ"));
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
		3���ǳ���  0���¼�
	*/
	Resource::school_map[10][10] = 3;
	Resource::school_map[11][10] = 3;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::Event, 0, "�������Ǹ��ľ�������еĳ���"));
	InteractiveEvent temp("Ӧ����һ��������Ϣ�ĵط�");
	Result selection1("����������Ϣһ���", "��������������һ������о�������", Result::TYPE::UpdatePlayerState, 0, 0, -5, 5);
	Result selection2("��������");
	temp.addResult(selection1);
	temp.addResult(selection2);
	Resource::interactionEvent_map.push_back(temp);
}

void Init::init_data()
{
	Resource::Event_queue.clear();

	Resource::itemBox_map.clear();

	/*
		ǰ����û�ã���Ϊ�±��Ǵ�2��ʼ�ģ�ǰ��������ռλ
	*/
	Resource::interaction_map.clear();
	Resource::interaction_map.push_back(Interaction());
	Resource::interaction_map.push_back(Interaction());

	/*
		���￪ʼ��ӿɻ�����Ʒ
	*/
	
	data1();
	data2();

}