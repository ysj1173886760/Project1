#include "UI.h"

bool UI::open_backpack = false;

bool UI::open_itemBox = false;

std::pair<int, int>UI::itemBox_pointer_left(0, 0);

std::pair<int, int>UI::itemBox_pointer_right(0, 0);

int UI::itemBox_pointer = 0;

std::pair<int, int>UI::backpack_pointer(0, 0);

Container UI::now_itemBox(0, 0);

int UI::interact_key = 0;

bool UI::open_event = false;

int UI::event_pointer = 0;

InteractiveEvent UI::now_event("");

bool UI::open_window = false;

Window UI::now_window("");

std::pair<int, int> UI::craft_pointer(0, 0);

bool UI::open_craft = false;

std::string UI::craft_name = "";

int UI::equip_pointer = 0;

bool UI::open_equip = false;