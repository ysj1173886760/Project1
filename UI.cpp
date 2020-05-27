#include "UI.h"

bool UI::open_backpack = false;

bool UI::open_itemBox = false;

std::pair<int, int>UI::itemBox_pointer(0, 0);

int UI::backpack_pointer = 0;

Container UI::now_itemBox(0, 0);

int UI::interact_key = 0;

bool UI::open_event = false;

int UI::event_pointer = 0;

InteractiveEvent UI::now_event("");