#include "Resource.h"


IMAGE Resource::player(0, 0);
IMAGE Resource::state(0, 0);
IMAGE Resource::backpack(0, 0);
IMAGE Resource::backpack_pointer(0, 0);
IMAGE Resource::itemBox(0, 0);
IMAGE Resource::eventWindow(0, 0);
IMAGE Resource::event_pointer(0, 0);
IMAGE Resource::Window(0, 0);
IMAGE Resource::craft_window(0, 0);
IMAGE Resource::zombie(0, 0);
IMAGE Resource::hit(0, 0);
IMAGE Resource::equip(0, 0);
IMAGE Resource::main(0, 0);
IMAGE Resource::begin(0, 0);
IMAGE Resource::main_pointer(0, 0);
IMAGE Resource::help(0, 0);
IMAGE Resource::help_page(0, 0);
IMAGE Resource::death_page(0, 0);
IMAGE Resource::loaddata(0, 0);
IMAGE Resource::deploy(0, 0);
IMAGE Resource::success(0, 0);
IMAGE Resource::hunter(0, 0);
IMAGE Resource::tyrant(0, 0);
IMAGE Resource::setting(0, 0);
IMAGE Resource::setting_page(0, 0);
IMAGE Resource::boss(0, 0);
IMAGE Resource::settlement(0, 0);

std::map<std::string, IMAGE>Resource::placeable_map;

std::map<std::string, IMAGE>Resource::map_image;

std::map<std::string, std::vector<detail>>Resource::placeable_position;

std::vector<Item*>Resource::item_map;

Container Resource::player_backpack(0, 0);

std::list<Event>Resource::Event_queue;

std::vector<Container>Resource::itemBox_map;

std::vector<Interaction*>Resource::interaction_map;

std::vector<InteractiveEvent>Resource::interactionEvent_map;

std::map<std::string, std::vector<Craft*>>Resource::craft_map;

GameTime Resource::Maintime(0, 0, 0, 0);

std::map<std::string, int>Resource::item_map_for_string;

std::map<std::string, int>Resource::placeableId_map;

std::map<std::string, std::vector<Enemy*>>Resource::zombie_map;

std::map<std::string, std::vector<std::vector<int>>>Resource::mainMap;

Astar Resource::myAstar;

Random Resource::myrandom;

std::map<std::string, std::string>Resource::zombie_spawn;