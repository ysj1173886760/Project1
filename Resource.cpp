#include "Resource.h"

IMAGE Resource::school(0, 0);
IMAGE Resource::player(0, 0);
IMAGE Resource::state(0, 0);
IMAGE Resource::backpack(0, 0);
IMAGE Resource::backpack_pointer(0, 0);
IMAGE Resource::itemBox(0, 0);

int Resource::school_map[30][30] = { 0 };

std::vector<Item>Resource::item_map;

Container Resource::player_backpack(0, 0);

std::list<Event>Resource::Event_queue;

std::vector<Container>Resource::itemBox_map;

std::vector<Interaction>Resource::interaction_map;