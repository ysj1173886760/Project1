#include "GameTime.h"

void GameTime::add() {//���һ�룬���ڻ���ʱ�䴦��
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
void GameTime::speadd_hou(int t) {//���Сʱ�����ڻ���ʱ�䴦��
	this->hours+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::speadd_min(int t) {//��ӷ��ӣ����ڻ���ʱ�䴦��
	this->minutes+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}
void GameTime::speadd_sec(int t) {//����ض����������ڻ���ʱ�䴦��
	this->seconds+=t;
	this->minutes += this->seconds / 60;
	this->hours += this->minutes / 60;
	this->days += this->hours / 24;
	this->seconds %= 60;
	this->minutes %= 60;
	this->hours %= 24;
}