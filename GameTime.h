#pragma once
#include<iostream>
#include<cmath>

class GameTime {
	public:
		int hours;
		int minutes;
		int seconds;
		int days;
		GameTime() {
			this->days = 0;
			this->hours = 0;
			this->seconds = 0;
			this->minutes = 0;
		}
		GameTime(int hou, int min, int sec, int day) {
			this->days = day;
			this->minutes = min;
			this->seconds = sec;
			this->hours = hou;
		}
		void add();
		void speadd_sec(int t);
		void add(int, int, int);
		void speadd_min(int t);
		void speadd_hou(int t);
};