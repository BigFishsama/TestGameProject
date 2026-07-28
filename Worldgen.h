#pragma once
#include "Manager.h"
#include "fishsouptools.h"
#include "Wall.h"
using namespace std;

inline bool checkedge(int x, int y,int style)
{
	if (x<1 || y<1 || x>map_weight || y>map_height) return 0;
	if (y == 1 && style == 0) return 0;
	if (y == map_height && style == 1) return 0;
	if (x == 1 && style == 2) return 0;
	if (x == map_weight && style == 3) return 0;
	//debug(x)debug(y)debug(style)
	return 1;
}
inline bool checkedge(tuple<int, int, int> u)
{
	return checkedge(get<0>(u), get<1>(u), get<2>(u));
}
inline pair<int, int> getNeighbor(int x, int y, int style)
{
	if (style == 0) return { x,y - 1 };
	else if (style == 1) return { x,y + 1 };
	else if (style == 2) return { x - 1,y };
	else return { x + 1,y };
}
inline void bombground(int stx, int sty, vector<tuple<int, int, int>>& tem_edge)
{
	map_ground[stx][sty] = 1;
	for (int t = 0;t <= 3;++t)
	{
		if (checkedge(stx, sty, t)) tem_edge.push_back({ stx,sty,t });
	}
}
//生成墙壁
void genWalls(int stx,int sty)
{
	//vector<vector<bool>> tem_map_wall
	vector<tuple<int, int, int>> tem_edge;

	//将初始位置，以及四周墙壁加入
	bombground(stx, sty, tem_edge);
	for (int t = 1;t <=map_height*map_weight/5;++t)
	{
		bombground(getRandomInt(1,map_weight), getRandomInt(1,map_height), tem_edge);
	}
	
	int tot_edge = (map_weight-1)*(map_height-1) + map_weight * 2 + map_height * 2;
	int del_number = getRandomInt(tot_edge/10*6,tot_edge/10*8);

	//Debug
	debug(stx)debug(sty)
	debug(tem_edge.size())
	debug(tot_edge)
	debug(del_number)


	for (int t = 1;t <= del_number;++t)
	{
		// x y style
		tuple<int, int, int> ran_edge = tem_edge[getRandomInt(0, tem_edge.size()-1)];
		bool spj = false;
		while(map_wall[get<0>(ran_edge)][get<1>(ran_edge)][get<2>(ran_edge)]==0||checkedge(ran_edge)==0)
		{
			ran_edge = tem_edge[getRandomInt(0, max(0, tem_edge.size() - 1))];
		}

		//删除这条边
		debug(get<0>(ran_edge))debug(get<1>(ran_edge))debug(get<2>(ran_edge))cout << endl;
		map_wall[get<0>(ran_edge)][get<1>(ran_edge)][get<2>(ran_edge)]=0;

		pair<int,int> tem_neighbor=getNeighbor(get<0>(ran_edge), get<1>(ran_edge), get<2>(ran_edge));

		if (tem_neighbor.first<1 || tem_neighbor.first >map_weight || tem_neighbor.second < 1 || tem_neighbor.second >map_height) continue;
		if (!map_ground[tem_neighbor.first][tem_neighbor.second])
		{
			map_ground[tem_neighbor.first][tem_neighbor.second] = 1;
			for (int t = 0;t <= 3;++t)
			{
				if (checkedge(tem_neighbor.first, tem_neighbor.second, t)) 
					tem_edge.push_back({ tem_neighbor.first,tem_neighbor.second,t });
			}
		}
	}

	int tem_wallx, tem_wally;
	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			if (t == 1 || (map_wall[i][t][0] && map_wall[i][t - 1][1])) map_wall[i][t][0] = 1;
			else map_wall[i][t][0] = 0;
			if (t == map_height || (map_wall[i][t][1] && map_wall[i][t + 1][0])) map_wall[i][t][1] = 1;
			else map_wall[i][t][1] = 0;
			if (i == 1 || (map_wall[i][t][2] && map_wall[i - 1][t][3])) map_wall[i][t][2] = 1;
			else map_wall[i][t][2] = 0;
			if (i == map_weight || (map_wall[i][t][3] && map_wall[i + 1][t][2])) map_wall[i][t][3] = 1;
			else map_wall[i][t][3] = 0;
		}
	}
	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			if (map_wall[i][t][0] && map_wall[i][t][1] && map_wall[i][t][2] && map_wall[i][t][3])
			{
				map_ground[i][t] = -1;
			}
		}
	}
	for (int t = 0, sty = 100;t < map_height;++t)
	{
		for (int i = 0, stx = (1400 - map_weight * ground_length) / 2;i < map_weight;++i)
		{
			if (map_ground[i+1][t+1] == -1)
			{
				Ground* u = new Ground(stx + i * ground_length, sty + t * ground_length, ground_length, RGB(48, 48, 48));
				background_object.push_back(u);
			}
			else
			{
				Ground* u = new Ground(stx + i * ground_length, sty + t * ground_length, ground_length);
				background_object.push_back(u);
			}
		}
	}
	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			debug(t)debug(i)debug(map_wall[i][t][0])debug(map_wall[i][t][1])debug(map_wall[i][t][2])debug(map_wall[i][t][3])cout << endl;
			if(map_wall[i][t][0])
			{
				tem_wallx = (1400 - map_weight * ground_length) / 2 + (i - 1) * ground_length;
				tem_wally = 100 + (t - 1) * ground_length;
				Wall* tem_wall = new Wall(tem_wallx, tem_wally, 0, ground_length);
				background_object.push_back(tem_wall);
			}
			if(map_wall[i][t][1])
			{
				tem_wallx = (1400 - map_weight * ground_length) / 2 + (i - 1) * ground_length;
				tem_wally = 100 + (t - 1) * ground_length+ground_length;
				Wall* tem_wall = new Wall(tem_wallx, tem_wally, 1, ground_length);
				background_object.push_back(tem_wall);
			}
			if (map_wall[i][t][2])
			{
				tem_wallx = (1400 - map_weight * ground_length) / 2 + (i - 1) * ground_length;
				tem_wally = 100 + (t - 1) * ground_length;
				Wall* tem_wall = new Wall(tem_wallx, tem_wally, 2, ground_length);
				background_object.push_back(tem_wall);
			}
			if(map_wall[i][t][3])
			{
				tem_wallx = (1400 - map_weight * ground_length) / 2 + (i - 1) * ground_length + ground_length;
				tem_wally = 100 + (t - 1) * ground_length ;
				Wall* tem_wall = new Wall(tem_wallx, tem_wally, 3, ground_length);
				background_object.push_back(tem_wall);
			}
		}
	}
}

void initWorld()
{
	//纵轴可选的方块个数
	int tem_ground_length[7] = { 2,3,5,6,8,10,12 };
	map_height = tem_ground_length[getRandomInt(0, 6)];

	//得到单个地板的边长
	ground_length = 600 / map_height;

	//计算相对于100的缩放等级
	scalelevel = 100.0 / ground_length;

	//此处不想横轴填满所以缩小了100
	int tem_ceil = 1300 / ground_length;
	map_weight = getRandomInt(min(tem_ceil, 5), tem_ceil);

	//随机玩家出生位置
	int tem_stx = getRandomInt(1, map_weight),tem_sty=getRandomInt(1,map_height);
	player.x = (1400 - map_weight * ground_length) / 2 + (tem_stx - 1) * ground_length+ground_length/2;
	player.y = 100 + (tem_sty - 1) * ground_length+ground_length/2;

	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			//所有地板默认不可用
			map_ground[i][t] = 0;

			//上下左右四个墙壁默认存在
			map_wall[i][t][0] = map_wall[i][t][1] = map_wall[i][t][2] = map_wall[i][t][3] = 1;
		}
	}
	genWalls(tem_stx,tem_sty);

	//日志
	cout << "Worldgen completed!\n";
	cout << "The details listed below:\n";
	cout << " map_height: " << map_height << '\n';
	cout << "map_weight: " << map_weight << '\n';
}