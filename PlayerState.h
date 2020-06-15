#pragma once
#include<string>
#include<map>

class PlayerState
{
	public:
		static int player_x;
		static int player_y;
		static int player_hp;
		static int player_food;
		static int player_water;
		static int player_fatigue;
		static std::string player_position;
		static int player_face;
		static int player_sanity;

		static int attack_min;
		static int attack_max;

		static int speed;
		static int step;

		static bool chased;

		static int bloat;		//ӷ�׶ȣ� Ӱ��������
		static int defense;		//������
		static std::map<std::string, bool>debuff;	//�쳣״̬
		static std::map<std::string, std::string>equip;	//������Ʒ

		static int experience;

		/*
			ͳ������
		*/
		static int kill_zombie;
};

