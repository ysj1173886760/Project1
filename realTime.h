#pragma once
#include<ctime>

class realTime
{
	public:
		time_t start_t, now_t;
		double diff_t;//时间差

		realTime()
		{
			diff_t = 0;
			start_t = 0;
			now_t = 0;
		}

		void gettime()
		{
			now_t = time(NULL);//读取当前系统时间
			diff_t = difftime(now_t, start_t);//单位秒
			start_t = time(NULL);//重设初始时间
		}
};

