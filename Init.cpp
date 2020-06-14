#include "Init.h"

void Init::init_image()
{
	loadimage(&Resource::player, _T("Resources\\test.png"));
	loadimage(&Resource::state, _T("Resources\\state.png"));
	loadimage(&Resource::backpack, _T("Resources\\backpack.png"));
	loadimage(&Resource::backpack_pointer, _T("Resources\\backpack_pointer.png"));
	loadimage(&Resource::itemBox, _T("Resources\\itemBox.png"));
	loadimage(&Resource::eventWindow, _T("Resources\\eventWindow.png"));
	loadimage(&Resource::event_pointer, _T("Resources\\event_pointer.png"));
	loadimage(&Resource::Window, _T("Resources\\window.png"));
	loadimage(&Resource::craft_window, _T("Resources\\craft.png"));
	loadimage(&Resource::zombie, _T("Resources\\zombie.png"));
	loadimage(&Resource::hit, _T("Resources\\hit.png"));
	loadimage(&Resource::equip, _T("Resources\\equip.png"));
	loadimage(&Resource::main, _T("Resources\\main.png"));
	loadimage(&Resource::begin, _T("Resources\\begin.png"));
	loadimage(&Resource::main_pointer, _T("Resources\\main_pointer.png"));
	loadimage(&Resource::help, _T("Resources\\help.png"));
	loadimage(&Resource::help_page, _T("Resources\\help_page.png"));

	/*
		placeable pic
	*/

	loadimage(&Resource::placeable_map["营火"], _T("Resources\\campfire.png"));
	loadimage(&Resource::placeable_map["武器台"], _T("Resources\\weaponcraft.png"));
	loadimage(&Resource::placeable_map["不详的武器台"], _T("Resources\\evilweaponcraft.png"));

	/*
		load map
	*/
	/*
	std::string now = "A1";
	char buff[50];
	for(int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			std::string temp1 = now;
			temp1[0] += i;
			temp1[1] += j;
			std::string temp2 = "Resources\\map\\" + temp1 + ".png";
			strcpy_s(buff, temp2.c_str());
			loadimage(&Resource::map_image[temp1], buff);
		}
	*/

}

void Init::init_player_state()
{
	PlayerState::player_x = 10;
	PlayerState::player_y = 20;
	PlayerState::player_hp = 100;
	PlayerState::player_food = 100;
	PlayerState::player_water = 100;
	PlayerState::player_fatigue = 0;
	PlayerState::player_position = "B7";
	PlayerState::player_face = 0;
	PlayerState::player_sanity = 100;
	PlayerState::attack_min = 10;
	PlayerState::speed = 10;
	PlayerState::step = 0;
}

/*
	0是可以通过的
	1是障碍
	2 到 2147483647 是 可交互物品
*/
void init_block(std::string now)
{
	char buff[50];
	std::string temp1 = "Resources\\map\\" + now + ".png";
	strcpy_s(buff, temp1.c_str());
	loadimage(&Resource::map_image[now], buff);

	std::vector<std::vector<int>>temp(30, std::vector<int>(30));
	try
	{
		std::fstream file;
		file.open("data\\map\\" + now + ".txt", std::ios::in);

		int x = 0, y = 0;
		while (1)
		{
			file >> x >> y;
			if (file.eof())
				break;
			temp[x][y] = 1;
		}
		file.close();
		Resource::mainMap[now] = temp;
		std::cout << now << " init complete" << std::endl;
	}
	catch (std::exception e)
	{
		std::cout << now << " " << e.what() << std::endl;
	}
}


void Init::init_map()
{
	std::string now = "A";

	for(int i = 0; i < 10; i++)
		for (int j = 1; j <= 15; j++)
		{
			std::string temp = now;
			temp[0] += i;
			init_block(temp + std::to_string(j));
		}
	init_block("house01");
	init_block("house02");
	init_block("house03");
	init_block("house04");
	init_block("house05");
	init_block("house06");
	init_block("house07");
	init_block("house08");
	init_block("house09");
	init_block("house10");
	init_block("house11");
	init_block("house12");
	init_block("house13");
	init_block("house14");
	init_block("house15");
	init_block("house16");
	init_block("house18");
	init_block("house19");
	init_block("house21");
	init_block("house17f1");
	init_block("house17f2");
	init_block("house20f1");
	init_block("house20f2");
	init_block("house22");
	init_block("house23");
	init_block("house24");
	init_block("house25");
	init_block("house26");
	init_block("house27");
	init_block("house28");
	init_block("house29");
	init_block("house30");
	init_block("house31");
	init_block("house32");
	init_block("house33");
	init_block("house34");
	init_block("house35");
	init_block("house36");
	init_block("house37");
	init_block("house38f1");
	init_block("house38f2");
	init_block("house39");
	init_block("house40");
	init_block("house41");
	init_block("house42");
	init_block("house43");
	init_block("house44");
	init_block("house45");
	init_block("house46");
	init_block("port_house");
	init_block("factoryf1");
	init_block("factoryf2");
	init_block("waterhouse");
}

void Init::init_easyx()
{
	setfillcolor(GREEN);
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
		jsonReader.parse(ifs, root); //从ifs中读取数据到jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//遍历数组[]
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
			else if (type == "cloth")
			{
				Cloth* newCloth = new Cloth();
				newCloth->description = temp["description"].asString();
				newCloth->event = temp["event"].asString();
				newCloth->name = temp["name"].asString();
				newCloth->pic_source = "Resources\\\\" + temp["pic"].asString();
				newCloth->time = temp["time"].asInt();
				newCloth->size = temp["size"].asInt();
				newCloth->type = Item::TYPE::Cloth;
				newCloth->bloat = temp["bloat"].asInt();
				newCloth->defense = temp["defense"].asInt();
				newCloth->where = temp["where"].asString();
				newItem = newCloth;
			}
			else if (type == "weapon")
			{
				Weapon* newWeapon = new Weapon();
				newWeapon->description = temp["description"].asString();
				newWeapon->event = temp["event"].asString();
				newWeapon->name = temp["name"].asString();
				newWeapon->pic_source = "Resources\\\\" + temp["pic"].asString();
				newWeapon->time = temp["time"].asInt();
				newWeapon->size = temp["size"].asInt();
				newWeapon->type = Item::TYPE::Weapon;
				newWeapon->attack_max = temp["attack_max"].asInt();
				newWeapon->attack_min = temp["attack_min"].asInt();
				newWeapon->where = temp["where"].asString();
				newItem = newWeapon;
			}
			else if (type == "backpack")
			{
				Backpack* newBackpack = new Backpack();
				newBackpack->description = temp["description"].asString();
				newBackpack->event = temp["event"].asString();
				newBackpack->name = temp["name"].asString();
				newBackpack->pic_source = "Resources\\\\" + temp["pic"].asString();
				newBackpack->time = temp["time"].asInt();
				newBackpack->size = temp["size"].asInt();
				newBackpack->capacity = temp["capacity"].asInt();
				newBackpack->type = Item::TYPE::Backpack;
				newBackpack->bloat = temp["bloat"].asInt();
				newBackpack->where = temp["where"].asString();
				newItem = newBackpack;
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
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 0, 0, 5, 0, 0, 0, 1, 60, "苹果", "香甜可口的苹果，和牛顿有某种关系", "你吃了个苹果，感觉还不错", "Resources\\apple.png"));
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 1, 0, 0, 5, 0, 0, 1, 60, "矿泉水", "一瓶普通的矿泉水，在这资源匮乏的末世显得异常罕见", "你喝了瓶水，口渴程度有所缓解", "Resources\\water.png"));
	//Resource::item_map.push_back(Item(Item::TYPE::Consumables, 2, 0, 0, 0, 0, 5, 1, 300, "任天堂的SWITCH(塞尔达传说)", "任天堂公司出品的SWITCH，上面插有塞尔达传说：荒野之息的卡带，即便是虚拟人物，里面的角色也让身处末世的你感到陪伴", "你玩了会儿switch，快乐++", "Resources\\switch.png"));
	load_data_from_json("data\\comestible.json");
	load_data_from_json("data\\material.json");
	load_data_from_json("data\\craft.json");
	load_data_from_json("data\\tool.json");
	load_data_from_json("data\\placeable.json");
	load_data_from_json("data\\equipments.json");
}

void Init::init_loot()
{

	/*
		玩家背包
	*/
	Resource::player_backpack.set(0, 5);			//设置空间
	Resource::item_map[Resource::item_map_for_string["白色T恤"]]->equip();
	Resource::item_map[Resource::item_map_for_string["运动裤"]]->equip();
	Resource::item_map[Resource::item_map_for_string["运动鞋"]]->equip();

	/*
		箱子
	*/
	
	int n = Resource::itemBox_map.size();
	int sumOfItem = Resource::item_map.size();
	std::cout << n << " " << sumOfItem << " " << std::endl;
	for (int i = 0; i < n; i++)
	{
		int maxx = 0, minn = 0;
		if (Resource::itemBox_map[i].rare == "low")
		{
			minn = 0;
			maxx = 5;
		}
		else if (Resource::itemBox_map[i].rare == "medium")
		{
			minn = 5;
			maxx = 10;
		}
		else if (Resource::itemBox_map[i].rare == "high")
		{
			minn = 10;
			maxx = 15;
		}
		int sum = Resource::myrandom.getRandom(minn, maxx);
		for (int j = 0; j < sum; j++)
		{
			int cnt = 0;
			int temp = Resource::myrandom.getRandom(0, sumOfItem - 1);
			while (!Resource::itemBox_map[i].canPut(Resource::item_map[temp]->name))
			{
				temp = Resource::myrandom.getRandom(0, sumOfItem - 1);
				cnt++;
				if (cnt > 5)break;
			}
			if (cnt > 5)break;
			Resource::itemBox_map[i].add(Resource::item_map[temp]->name);
		}
	}

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
		jsonReader.parse(ifs, root); //从ifs中读取数据到jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//遍历数组[]
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
				newContainer.rare = temp["rare"].asString();
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
						newUpdate->des = temp["result"][i]["des"].asString();			//选项
						newUpdate->result = temp["result"][i]["result_des"].asString();	//做完选项后的后果
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
						newOpen->type = Result::TYPE::OpenCraftWindow;
						newOpen->window_name = temp["result"][i]["name"].asString();
						newResult = newOpen;
					}
					else if (resultType == "change")
					{
						ChangePos* newChange = new ChangePos();
						newChange->des = temp["result"][i]["des"].asString();
						newChange->type = Result::TYPE::ChangePos;
						newChange->map_name = temp["result"][i]["map_name"].asString();
						newChange->x = temp["result"][i]["x"].asInt();
						newChange->y = temp["result"][i]["y"].asInt();
						newResult = newChange;
					}

					if (newResult != NULL)
					{
						newInteractiveEvent.addResult(newResult);
					}
				}
				newInteraction = newInteractEvent;
				Resource::interactionEvent_map.push_back(newInteractiveEvent);
			}

			std::string map_name = temp["map_name"].asString();		//获得地图名字
			int n = temp["pos"].size();								//坐标数量
			int id = Resource::interaction_map.size();				//key值

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
		jsonReader.parse(ifs, root); //从ifs中读取数据到jsonRoot

		for (Json::Value::iterator it = root.begin(); it != root.end(); it++)//遍历数组[]
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
				else if (resultType == "break")
				{
					Break* newBreak = new Break();
					newBreak->type = Result::TYPE::Break;
					newBreak->des = temp["result"][i]["des"].asString();
					newResult = newBreak;
				}

				if (newResult != NULL)
				{
					newInteractiveEvent.addResult(newResult);
				}
			}
			Resource::interactionEvent_map.push_back(newInteractiveEvent);

			int id = Resource::interaction_map.size();				//key值
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
	
		2号是垃圾桶  0号容器
	
	Resource::school_map[28][19] = 2;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::ItemBox, 0, "求生欲使你忍住刺鼻的味道翻了翻这个垃圾桶"));
	Container temp(0, 20);
	temp.add("苹果", 10);
	Resource::itemBox_map.push_back(temp);
}
*/
/*
void data2()
{
	
		3号是长椅  0号事件
	
	Resource::school_map[10][10] = 3;
	Resource::school_map[11][10] = 3;
	Resource::interaction_map.push_back(Interaction(Interaction::TYPE::Event, 0, "看起来是个颇具有年代感的长椅"));
	InteractiveEvent temp("应该是一个可以休息的地方");

	Result *newResult = NULL;
	UpdatePlayerState *newnode = new UpdatePlayerState();
	newnode->des = "在椅子上休息一会儿";
	newnode->result = "你在椅子上躺了一会儿，感觉还不错";
	newnode->type = Result::TYPE::UpdatePlayerState;
	newnode->food = 10;
	newResult = newnode;
	//Result selection1("在椅子上休息一会儿", "你在椅子上躺了一会儿，感觉还不错", Result::TYPE::UpdatePlayerState, 0, 0, -5, 5, 0, 45, 0);
	//Result selection2("算了算了");
	temp.addResult(newResult);
	//temp.addResult(selection2);
	Resource::interactionEvent_map.push_back(temp);
}
*/

void create_zombie(int x, int y, std::string map_name)
{
	zombie* newzombie = new zombie();
	newzombie->hp = 30;
	newzombie->name = "普通僵尸";
	newzombie->x = x;
	newzombie->y = y;
	newzombie->speed = 10;
	newzombie->chaseRange = 5;
	newzombie->alive = true;
	newzombie->id = -1 - Resource::zombie_map[map_name].size();
	newzombie->attack_min = 5;
	Resource::mainMap[map_name][x][y] = newzombie->id;
	Resource::zombie_map[map_name].push_back(newzombie);
}
void Init::init_data()
{
	Resource::Event_queue.clear();

	Resource::itemBox_map.clear();

	/*
		前两个没用，因为下标是从2开始的，前两个用来占位
	*/
	Resource::interaction_map.clear();
	Resource::interaction_map.push_back(new Interaction());
	Resource::interaction_map.push_back(new Interaction());

	/*
		这里开始添加可互动物品
	*/
	
	//data1();
	//data2();

	load_event_from_json("data\\interactiveEvent.json");
	load_event_from_json("data\\itembox.json");
	load_placeable_event_from_json("data\\placeableEvent.json");

	/*
		测试敌人
	*/
	
	//create_zombie(25, 25);
	//create_zombie(25, 26);
	std::string first = "A";
	for(int i = 0; i < 10; i++)
		for (int j = 1; j <= 15; j++)
		{
			std::string now = first;
			now[0] += i;
			now += std::to_string(j);
			for (int k = 0; k < 3; k++)
			{
				int x = Resource::myrandom.getRandom(1, 28);
				int y = Resource::myrandom.getRandom(1, 28);
				int cnt = 0;
				while (Resource::mainMap[now][x][y] != 0)
				{
					cnt++;
					x = Resource::myrandom.getRandom(1, 28);
					y = Resource::myrandom.getRandom(1, 28);
					if (cnt > 5)break;
				}
				if (cnt > 5)break;
				create_zombie(x, y, now);
			}
		}
}
