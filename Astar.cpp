#include "Astar.h"

int H(int x, int y)
{
	return (abs(PlayerState::player_x - x) + abs(PlayerState::player_y - y));
}

bool operator<(const node& a, const node& b)
{
	return a.f > b.f;
}

void Astar::reset()
{
	while (!this->pq.empty())
		pq.pop();
	memset(dis, 0x3f, sizeof(dis));
	memset(closelist, 0, sizeof(closelist));
	memset(pre, 0, sizeof(pre));
}

std::pair<int, int> Astar::calc(int x, int y)
{
	int tarx = PlayerState::player_x;
	int tary = PlayerState::player_y;
	std::string pos = PlayerState::player_position;
	
	dis[x][y] = 0;
	node* begin = new node(x, y, H(x, y));
	pq.push(begin);
	while (!pq.empty())
	{
		node* now = pq.top();
		pq.pop();
		if (closelist[now->x][now->y])continue;
		closelist[now->x][now->y] = true;
		if (now->x == tarx && now->y == tary)
		{
			//找到终点
			node* temp = now;
			while (pre[temp->x][temp->y] != begin)
				temp = pre[temp->x][temp->y];
			return std::make_pair(temp->x, temp->y);
		}
		for (int i = 0; i < 4; i++)
		{
			int nx = now->x + dx[i];
			int ny = now->y + dy[i];
			if (nx < 0 || nx >= 30 || ny < 0 || ny >= 30 || Resource::mainMap[pos][nx][ny] != 0 || closelist[nx][ny])
				continue;
			if (dis[nx][ny] > dis[now->x][now->y] + 1)//合法节点继续拓展
			{
				dis[nx][ny] = dis[now->x][now->y] + 1;
				pre[nx][ny] = now;
				node* newnode = new node(nx, ny, dis[nx][ny] + H(x, y));
				pq.push(newnode);
			}
		}
	}
	return std::make_pair(x, y);
}