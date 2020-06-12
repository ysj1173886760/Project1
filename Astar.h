#pragma once
#include"Resource.h"
#include"PlayerState.h"
#include<queue>
#include<cstring>

struct node
{
	int x;
	int y;
	int f;	//f = g + h

	node(int x, int y, int f)
	{
		this->x = x;
		this->y = y;
		this->f = f;
	}
};

struct cmp
{
	bool operator()(node* &a, node* &b) const
	{
		return a->f > b->f;
	}
};

class Astar
{
	public:
		std::priority_queue<node*, std::vector<node*>, cmp>pq;
		node* pre[30][30];
		int dis[30][30];
		bool closelist[30][30];
		int dx[4];
		int dy[4];

		Astar() 
		{
			dx[0] = 0;
			dx[1] = 1;
			dx[2] = 0;
			dx[3] = -1;
			dy[0] = 1;
			dy[1] = 0;
			dy[2] = -1;
			dy[3] = 0;
		}
		void reset();
		std::pair<int, int> calc(int, int);
};
