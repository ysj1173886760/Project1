#include "Init.h"

void Init::init_image()
{
	loadimage(&Resource::school, _T("Resources\\school.png"));
	loadimage(&Resource::player, _T("Resources\\test.png"));
	loadimage(&Resource::state, _T("Resources\\state.png"));
	loadimage(&Resource::backpack, _T("Resources\\backpack.png"));
	loadimage(&Resource::backpack_pointer, _T("Resources\\backpack_pointer.png"));
	loadimage(&Resource::itemBox, _T("Resources\\itemBox.png"));
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
}

/*
	0�ǿ���ͨ����
	1���ϰ�
	2 �� 2147483647 �� �ɽ�����Ʒ
*/
void school_init()
{
	Resource::school_map[0][6] = 1;
	Resource::school_map[0][7] = 1;
	Resource::school_map[1][8] = 1;
	Resource::school_map[1][9] = 1;
	Resource::school_map[1][10] = 1;
	Resource::school_map[1][11] = 1;
	Resource::school_map[1][12] = 1;
	Resource::school_map[1][13] = 1;
	Resource::school_map[0][14] = 1;
	Resource::school_map[1][14] = 1;
	Resource::school_map[2][14] = 1;
	Resource::school_map[3][14] = 1;
	Resource::school_map[4][14] = 1;
	Resource::school_map[5][14] = 1;
	Resource::school_map[6][14] = 1;
	Resource::school_map[7][14] = 1;
	Resource::school_map[8][14] = 1;
	Resource::school_map[9][14] = 1;
	Resource::school_map[10][14] = 1;
	Resource::school_map[11][14] = 1;
	Resource::school_map[2][15] = 1;
	Resource::school_map[3][15] = 1;
	Resource::school_map[4][15] = 1;
	Resource::school_map[5][15] = 1;
	Resource::school_map[6][15] = 1;
	Resource::school_map[7][15] = 1;
	Resource::school_map[8][15] = 1;
	Resource::school_map[9][15] = 1;
	Resource::school_map[10][15] = 1;
	Resource::school_map[11][15] = 1;
	Resource::school_map[12][13] = 1;
	Resource::school_map[12][14] = 1;
	Resource::school_map[13][13] = 1;
	Resource::school_map[13][14] = 1;
	Resource::school_map[14][13] = 1;
	Resource::school_map[14][14] = 1;
	Resource::school_map[18][13] = 1;
	Resource::school_map[19][13] = 1;
	Resource::school_map[20][13] = 1;
	Resource::school_map[21][13] = 1;
	Resource::school_map[22][13] = 1;
	Resource::school_map[18][14] = 1;
	Resource::school_map[19][14] = 1;
	Resource::school_map[20][14] = 1;
	Resource::school_map[21][14] = 1;
	Resource::school_map[22][14] = 1;
	Resource::school_map[23][14] = 1;
	Resource::school_map[23][15] = 1;
	Resource::school_map[24][15] = 1;
	Resource::school_map[24][16] = 1;
	Resource::school_map[25][16] = 1;
	Resource::school_map[25][17] = 1;
	Resource::school_map[26][17] = 1;
	Resource::school_map[26][18] = 1;
	Resource::school_map[27][17] = 1;
	Resource::school_map[27][18] = 1;
	Resource::school_map[28][17] = 1;
	Resource::school_map[28][18] = 1;
	Resource::school_map[28][19] = 1;
	Resource::school_map[29][16] = 1;
	Resource::school_map[29][15] = 1;
	Resource::school_map[29][14] = 1;
	Resource::school_map[29][13] = 1;
	Resource::school_map[29][12] = 1;
	Resource::school_map[29][11] = 1;
	Resource::school_map[29][10] = 1;
	Resource::school_map[29][9] = 1;
	Resource::school_map[29][8] = 1;
	Resource::school_map[29][7] = 1;
	Resource::school_map[29][20] = 1;
	Resource::school_map[29][21] = 1;
	Resource::school_map[29][22] = 1;
	Resource::school_map[29][23] = 1;
	Resource::school_map[29][24] = 1;
	Resource::school_map[29][25] = 1;

	Resource::school_map[28][19] = 2;
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

void Init::init_data()
{
	Resource::Event_queue.clear();

	Resource::itemBox_map.clear();

	/*
		ǰ����û�ã���Ϊ�±��Ǵ�2��ʼ�ģ�ǰ��������ռλ
	*/
	Resource::interaction_map.clear();
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0));
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0));

	/*
		���￪ʼ��ӿɻ�����Ʒ
	*/

	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0));
	Container temp(20, 20);
	temp.add(0);
	temp.add(0);
	temp.add(0);
	temp.add(0);
	Resource::itemBox_map.push_back(temp);

}