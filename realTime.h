#pragma once
#include<ctime>

class realTime
{
	public:
		time_t start_t, now_t;
		double diff_t;//ʱ���

		realTime()
		{
			diff_t = 0;
			start_t = 0;
			now_t = 0;
		}

		void gettime()
		{
			now_t = time(NULL);//��ȡ��ǰϵͳʱ��
			diff_t = difftime(now_t, start_t);//��λ��
			start_t = time(NULL);//�����ʼʱ��
		}
};

