#pragma once


#include"Init.h"
#include"Resource.h"
#include"PlayerState.h"
#include"UI.h"



#define KEYDOWN(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEYUP(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 0 : 1)
#define BLOCK 24