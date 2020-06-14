#pragma once

/*
	使用旧的jsoncpp api会报错，需要加上这个
*/
#if defined(__GNUC__)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif defined(_MSC_VER)
#pragma warning(disable : 4996)
#endif

#include"Resource.h"
#include"PlayerState.h"
#include"Container.h"
#include "json/json.h"
#include "json/json-forwards.h"
#include"Random.h"
#include<fstream>
#include<exception>
#include<iostream>
#include<fstream>

#define BLOCK 24

class Init
{
	public:
		static void init_image();
		static void init_player_state();
		static void init_map();
		static void init_item();
		static void init_loot();
		static void init_data();
		static void init_easyx();
};

