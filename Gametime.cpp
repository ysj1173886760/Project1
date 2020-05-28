#include "GameTime.h"

void GameTime::add() {//添加一秒，用于基本时间处理
	this->seconds++;
	this->minutes +=this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::add(int sec, int min, int hou) {
	this->seconds += sec;
	this->minutes += min;
	this->hours += hou;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::speadd_hou(int t) {//添加小时，用于基本时间处理
	this->hours+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::speadd_min(int t) {//添加分钟，用于基本时间处理
	this->minutes+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::speadd_sec(int t) {//添加特定秒数，用于基本时间处理
	this->seconds+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}