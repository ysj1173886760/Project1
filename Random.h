#pragma once
#include<iostream>
#include<stdlib.h>
#include<algorithm>
#include <time.h>

class Random {
	public:
		int randnum_int;
		double randnum_double;
		int rand_seed;
		Random() {
			randnum_double = 0;
			randnum_int = 0;
			rand_seed = time(0);
		}
		Random(int num_int, double num_double,int randseed) {
			this->randnum_double = num_double;
			this->randnum_int = num_int;
			this->rand_seed = randseed;
		}
		void frand_ori() {//默认范围取随机数
			srand((int)this->rand_seed);
			this->randnum_int = rand();
			//this->randnum_double = rand() + rand() / (RAND_MAX + 1.0);
			this->rand_seed = (this->randnum_int * ((int)time(0))) % 1000007;
		}
		void frand_range(int a, int b) {//取一个范围内的随机数
			srand((int)this->rand_seed);
			//this->randnum_double = ((double)rand() / RAND_MAX) * (b - a) + a;
			this->randnum_int = (rand() % (b - a + 1)) + a;
			this->rand_seed = (this->randnum_int * ((int)time(0))) % 1000007;
		}
		int getRandom(int a, int b)
		{
			frand_range(a, b);
			return randnum_int;
		}
};