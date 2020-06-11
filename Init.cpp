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
	loadimage(&Resource::Window, _T("Resources\\window.png"));
	loadimage(&Resource::craft_window, _T("Resources\\craft.png"));
	loadimage(&Resource::way_to_school, _T("Resources\\way_to_school.png"));
	loadimage(&Resource::placeable_map["Ӫ��"], _T("Resources\\campfire.png"));
	loadimage(&Resource::zombie, _T("Resources\\zombie.png"));
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
	PlayerState::attack_min = 10;
}

/*
	0�ǿ���ͨ����
	1���ϰ�
	2 �� 2147483647 �� �ɽ�����Ʒ
*/
void school_init()
{
	std::vector<std::vector<int>>school_map(30, std::vector<int>(30));
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
			school_map[x][y] = 1;
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	Resource::mainMap["������ѧУ"] = school_map;
}

void wayToSchool_init()
{
	std::vector<std::vector<int>>way_to_school_map(30, std::vector<int>(30));
	try
	{
		std::fstream file;
		file.open("data\\way_to_school.txt", std::ios::in);

		int x = 0, y = 0;
		while (1)
		{
			file >> x >> y;
			if (file.eof())
				break;
			way_to_school_map[x][y] = 1;
		}
	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	Resource::mainMap["ͨ��ѧУ��·"] = way_to_school_map;
}

void Init::init_map()
{
	
	school_init();
	wayToSchool_init();
}

void load_data_from_json(std::string source)
{
	try
	{
		std::ifstream ifs;
		ifs.open(source);

		if (!ifs)
		{
			std::cout << "file open error";
		}

		Json::Value root;
		root.clear();

		Json::Reader jsonReader;
		jsonReader.parse(ifs, root); //��ifs�ж�ȡ���ݵ�jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//��������[]
		{
			Json::Value temp = (*it);
			std::string type = temp["type"].asString();
			Item* newItem = NULL;

			if (type == "comestible")
			{
				Comestible *newComsetible = new Comestible();
				newComsetible->description = temp["description"].asString();
				newComsetible->event = temp["event"].asString();
				newComsetible->name = temp["name"].asString();
				newComsetible->pic_source = "Resources\\\\" + temp["pic"].asString();
				newComsetible->food = temp["food"].asInt();
				newComsetible->water = temp["water"].asInt();
				newComsetible->fagitue = temp["fagitue"].asInt();
				newComsetible->time = temp["time"].asInt();
				newComsetible->size = temp["size"].asInt();
				newComsetible->type = Item::TYPE::Comestible;
				newItem = newComsetible;

				//std::cout << newComsetible->pic_source<<std::endl;
			}
			else if (type == "material")
			{
				Material* newMaterial = new Material();
				newMaterial->description = temp["description"].asString();
				newMaterial->event = temp["event"].asString();
				newMaterial->name = temp["name"].asString();
				newMaterial->pic_source = "Resources\\\\" + temp["pic"].asString();
				newMaterial->time = temp["time"].asInt();
				newMaterial->size = temp["size"].asInt();
				newMaterial->type = Item::TYPE::Material;
				newItem = newMaterial;
			}
			else if(type == "craft")
			{
				Craft* newCraft = new Craft();
				newCraft->product = temp["product"].asString();
				newCraft->event = temp["event"].asString();
				newCraft->time = temp["time"].asInt();
				int n = temp["need"].size();
				for (int i = 0; i < n; i++)
					newCraft->add(temp["need"][i]["name"].asString(), temp["need"][i]["sum"].asInt());
				std::string name = temp["name"].asString();
				Resource::craft_map[name].push_back(newCraft);
			}
			else if (type == "tool")
			{
				Tool* newTool = new Tool();
				newTool->name = temp["name"].asString();
				newTool->description = temp["description"].asString();
				newTool->pic_source = "Resources\\\\" + temp["pic"].asString();
				newTool->size = temp["size"].asInt();
				newTool->type = Item::TYPE::Tool;
				newItem = newTool;
			}
			else if (type == "placeable")
			{
				Placeable* newPlaceable = new Placeable();
				newPlaceable->name = temp["name"].asString();
				newPlaceable->description = temp["description"].asString();
				newPlaceable->pic_source = "Resources\\\\" + temp["pic"].asString();
				newPlaceable->size = temp["size"].asInt();
				newPlaceable->time = temp["time"].asInt();
				newPlaceable->event = temp["event"].asString();
				newPlaceable->type = Item::TYPE::Placeable;
				newItem = newPlaceable;
			}

			if (newItem != NULL)
			{
				Resource::item_map.push_back(newItem);
				if (Resource::item_map_for_string.find(newItem->name) == Resource::item_map_for_string.end())
				{
					Resource::item_map_for_string[newItem->name] = Resource::item_map.size() - 1;
				}
				else
				{
					std::cout << "error! item name already exists" << std::endl;
				}
			}

		}
		ifs.close();
	}
	catch (Json::LogicError e)
	{
		std::cout << e.what();
	}
}

void Init::init_item()
{
	Resource::item_map.clear();
	Resource::item_map_for_string.clear();
	Resource::craft_map.clear();
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 0, 0, 5, 0, 0, 0, 1, 60, "ƻ��", "����ɿڵ�ƻ������ţ����ĳ�ֹ�ϵ", "����˸�ƻ�����о�������", "Resources\\apple.png"));
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 1, 0, 0, 5, 0, 0, 1, 60, "��Ȫˮ", "һƿ��ͨ�Ŀ�Ȫˮ��������Դ�ѷ���ĩ���Ե��쳣����", "�����ƿˮ���ڿʳ̶���������", "Resources\\water.png"));
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 2, 0, 0, 0, 0, 5, 1, 300, "�����õ�SWITCH(�����ﴫ˵)", "�����ù�˾��Ʒ��SWITCH��������������ﴫ˵����Ұ֮Ϣ�Ŀ����������������������Ľ�ɫҲ����ĩ������е����", "�����˻��switch������++", "Resources\\switch.png"));
	load_data_from_json("data\\comestible.json");
	load_data_from_json("data\\material.json");
	load_data_from_json("data\\craft.json");
	load_data_from_json("data\\tool.json");
	load_data_from_json("data\\placeable.json");
}

void Init::init_loot()
{

	/*
		��ұ���
	*/
	Resource::player_backpack.set(0, 25);			//���ÿռ�
	Resource::player_backpack.add("ƻ��", 10);
	Resource::player_backpack.add("ľ��", 3);
	Resource::player_backpack.add("��", 2);
	Resource::player_backpack.add("��Ȫˮ");
	Resource::player_backpack.add("Ӫ��", 2);
}

void load_event_from_json(std::string source)
{
	try
	{
		std::ifstream ifs;
		ifs.open(source);

		if (!ifs)
		{
			std::cout << "file open error";
		}

		Json::Value root;
		root.clear();

		Json::Reader jsonReader;
		jsonReader.parse(ifs, root); //��ifs�ж�ȡ���ݵ�jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//��������[]
		{
			Json::Value temp = (*it);
			std::string type = temp["type"].asString();
			Interaction *newInteraction;
			if (type == "itembox")
			{
				ItemBox* newItemBox = new ItemBox();
				int newId = Resource::itemBox_map.size();
				newItemBox->key = newId;
				newItemBox->des = temp["des"].asString();
				newItemBox->type = Interaction::TYPE::ItemBox;

				int size = temp["size"].asInt();
				Container newContainer(size);
				Resource::itemBox_map.push_back(newContainer);
				newInteraction = newItemBox;
			}
			else if (type == "event")
			{
				InteractEvent* newInteractEvent = new InteractEvent();
				int newId = Resource::interactionEvent_map.size();
				newInteractEvent->key = newId;
				newInteractEvent->des = temp["des"].asString();
				newInteractEvent->type = Interaction::TYPE::Event;

				InteractiveEvent newInteractiveEvent;
				newInteractiveEvent.des = temp["event_des"].asString();

				
				int n = temp["result"].size();
				for (int i = 0; i < n; i++)
				{
					Result* newResult = NULL;
					std::string resultType = temp["result"][i]["type"].asString();
					if (resultType == "update")
					{
						UpdatePlayerState* newUpdate = new UpdatePlayerState();
						newUpdate->des = temp["result"][i]["des"].asString();			//ѡ��
						newUpdate->result = temp["result"][i]["result_des"].asString();	//����ѡ���ĺ��
						newUpdate->type = Result::TYPE::UpdatePlayerState;
						newUpdate->food = temp["result"][i]["food"].asInt();
						newUpdate->water = temp["result"][i]["water"].asInt();
						newUpdate->fatigue = temp["result"][i]["fatigue"].asInt();
						newUpdate->sanity = temp["result"][i]["sanity"].asInt();
						newResult = newUpdate;
					}
					else if (resultType == "nothing")
					{
						DoNothing* newNothing = new DoNothing();
						newNothing->des = temp["result"][i]["des"].asString();
						newNothing->type = Result::TYPE::DoNothing;
						newResult = newNothing;
					}
					else if (resultType == "craft_window")
					{
						OpenCraftWindow* newOpen = new OpenCraftWindow();
						newOpen->des = temp["result"][i]["des"].asString();
						newOpen->type = Result::TYPE::UpdatePlayerState;
						newOpen->window_name = temp["result"][i]["name"].asString();
						newResult = newOpen;
					}

					if (newResult != NULL)
					{
						newInteractiveEvent.addResult(newResult);
					}
				}
				newInteraction = newInteractEvent;
				Resource::interactionEvent_map.push_back(newInteractiveEvent);
			}

			std::string map_name = temp["map_name"].asString();		//��õ�ͼ����
			int n = temp["pos"].size();								//��������
			int id = Resource::interaction_map.size();				//keyֵ

			for (int i = 0; i < n; i++)
			{
				int x = temp["pos"][i]["x"].asInt();
				int y = temp["pos"][i]["y"].asInt();
				Resource::mainMap[map_name][x][y] = id;
			}

			Resource::interaction_map.push_back(newInteraction);
		}
		ifs.close();
	}
	catch (Json::LogicError e)
	{
		std::cout << e.what();
	}
}

void load_placeable_event_from_json(std::string source)
{
	try
	{
		std::ifstream ifs;
		ifs.open(source);

		if (!ifs)
		{
			std::cout << "file open error";
		}

		Json::Value root;
		root.clear();

		Json::Reader jsonReader;
		jsonReader.parse(ifs, root); //��ifs�ж�ȡ���ݵ�jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//��������[]
		{
			Json::Value temp = (*it);
			std::string type = temp["type"].asString();
			PlaceableEvent* newPlaceableEvent = new PlaceableEvent();
			int newId = Resource::interactionEvent_map.size();
			newPlaceableEvent->key = newId;
			newPlaceableEvent->des = temp["des"].asString();
			newPlaceableEvent->type = Interaction::TYPE::PlaceableEvent;
			newPlaceableEvent->name = temp["name"].asString();

			InteractiveEvent newInteractiveEvent;
			newInteractiveEvent.des = temp["event_des"].asString();


			int n = temp["result"].size();
			for (int i = 0; i < n; i++)
			{
				Result* newResult = NULL;
				std::string resultType = temp["result"][i]["type"].asString();
				if (resultType == "nothing")
				{
					DoNothing* newNothing = new DoNothing();
					newNothing->des = temp["result"][i]["des"].asString();
					newNothing->type = Result::TYPE::DoNothing;
					newResult = newNothing;
				}
				else if (resultType == "craft_window")
				{
					OpenCraftWindow* newOpen = new OpenCraftWindow();
					newOpen->des = temp["result"][i]["des"].asString();
					newOpen->type = Result::TYPE::OpenCraftWindow;
					newOpen->window_name = temp["result"][i]["name"].asString();
					newResult = newOpen;
				}

				if (newResult != NULL)
				{
					newInteractiveEvent.addResult(newResult);
				}
			}
			Resource::interactionEvent_map.push_back(newInteractiveEvent);

			int id = Resource::interaction_map.size();				//keyֵ
			Resource::placeableId_map[newPlaceableEvent->name] = id;
			Resource::interaction_map.push_back(newPlaceableEvent);
		}
		ifs.close();
	}
	catch (Json::LogicError e)
	{
		std::cout << e.what();
	}
}
/*
void data1()
{
	
		2��������Ͱ  0������
	
	Resource::school_map[28][19] = 2;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0, "������ʹ����ס�̱ǵ�ζ�����˷��������Ͱ"));
	Container temp(0, 20);
	temp.add("ƻ��", 10);
	Resource::itemBox_map.push_back(temp);
}
*/
/*
void data2()
{
	
		3���ǳ���  0���¼�
	
	Resource::school_map[10][10] = 3;
	Resource::school_map[11][10] = 3;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::Event, 0, "�������Ǹ��ľ�������еĳ���"));
	InteractiveEvent temp("Ӧ����һ��������Ϣ�ĵط�");

	Result *newResult = NULL;
	UpdatePlayerState *newnode = new UpdatePlayerState();
	newnode->des = "����������Ϣһ���";
	newnode->result = "��������������һ������о�������";
	newnode->type = Result::TYPE::UpdatePlayerState;
	newnode->food = 10;
	newResult = newnode;
	//Result selection1("����������Ϣһ���", "��������������һ������о�������", Result::TYPE::UpdatePlayerState, 0, 0, -5, 5, 0, 45, 0);
	//Result selection2("��������");
	temp.addResult(newResult);
	//temp.addResult(selection2);
	Resource::interactionEvent_map.push_back(temp);
}
*/
void Init::init_data()
{
	Resource::Event_queue.clear();

	Resource::itemBox_map.clear();

	/*
		ǰ����û�ã���Ϊ�±��Ǵ�2��ʼ�ģ�ǰ��������ռλ
	*/
	Resource::interaction_map.clear();
	Resource::interaction_map.push_back(new Interaction());
	Resource::interaction_map.push_back(new Interaction());

	/*
		���￪ʼ��ӿɻ�����Ʒ
	*/
	
	//data1();
	//data2();

	load_event_from_json("data\\interactiveEvent.json");
	load_event_from_json("data\\itembox.json");
	load_placeable_event_from_json("data\\placeableEvent.json");

	/*
		���Ե���
	*/
	zombie* newzombie = new zombie();
	newzombie->hp = 30;
	newzombie->x = 25;
	newzombie->y = 25;
	newzombie->speed = 10;
	newzombie->chaseRange = 5;
	newzombie->alive = true;
	newzombie->id = -1 - Resource::zombie_map["������ѧУ"].size();
	newzombie->attack_min = 5;
	Resource::mainMap["������ѧУ"][25][25] = -1;
	Resource::zombie_map["������ѧУ"].push_back(newzombie);
}
