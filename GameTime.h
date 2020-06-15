#pragma once
#include<iostream>
#include<cmath>

class GameTime {
	public:
		int hours;
		int minutes;
		int seconds;
		int days;
		int previous_minutes;
		int previous_hours;
		GameTime() {
			this->days = 0;
			this->hours = 0;
			this->seconds = 0;
			this->minutes = 0;
			this->previous_minutes = 0;
			this->previous_hours = 0;
		}
		GameTime(int hou, int min, int sec, int day) {
			this->days = day;
			this->minutes = min;
			this->seconds = sec;
			this->hours = hou;
			this->previous_minutes = 0;
			this->previous_hours = 0;
		}
		void add();
		void speadd_sec(int t);
		void add(int, int, int);
		void speadd_min(int t);
		void speadd_hou(int t);
		void set(int hou, int min, int sec, int day) {
			this->days = day;
			this->minutes = min;
			this->seconds = sec;
			this->hours = hou;
			this->previous_minutes = min;
			this->previous_hours = hou;
		}
		int getPastTime()
		{
			int ans = minutes - previous_minutes;
			ans += ((hours - previous_hours + 24) % 24) * 60;
			previous_hours = hours;
			previous_minutes = minutes;
			return ans;
		}
};