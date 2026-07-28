#pragma once
#include "Manager.h"
#include "fishsouptools.h"
#include "Wall.h"
using namespace std;

//检查该边是否添加合法
inline bool checkedge(int x, int y,int style)
{
	if (x<1 || y<1 || x>map_weight || y>map_height) return 0;
	if (y == 1 && style == 0) return 0;
	if (y == map_height && style == 1) return 0;
	if (x == 1 && style == 2) return 0;
	if (x == map_weight && style == 3) return 0;
	return 1;
}
inline bool checkedge(tuple<int, int, int> u)
{
	return checkedge(get<0>(u), get<1>(u), get<2>(u));
}

//由点的一个边得到它对应的邻点
//注意，邻点不一定合法，需要判断
inline pair<int, int> getNeighbor(int x, int y, int style)
{
	if (style == 0) return { x,y - 1 };
	else if (style == 1) return { x,y + 1 };
	else if (style == 2) return { x - 1,y };
	else return { x + 1,y };
}

//暴力将点和边插入
inline void bombground(int x, int t, vector<tuple<int, int, int>>& tem_edge)
{
	map_ground[x][t] = 1;
	for (int t = 0;t <= 3;++t)
	{
		if (checkedge(x, t, t)) tem_edge.push_back({ x,t,t });
	}
}

//生成墙壁算法
//核心思路，将若干个点插入队列作为备选点和备选边，之后每次从其中删除，这样子生成的图会使得中心扩散（因为初始点的关联边被删可能性更大）
//特点：①地图生成质量表现不稳定，②图很难完全联通，③可能出现大片留白
void genWalls()
{
	//存储待删边
	vector<tuple<int, int, int>> tem_edge;

	//将若干随机位置，以及四周墙壁加入
	int tem_rantime = map_height * map_weight/4;
	for (int t = 1;t <=tem_rantime;++t)
	{
		bombground(getRandomInt(1,max(1,map_weight)), getRandomInt(1,max(1,map_height)), tem_edge);
	}

	//计算边总数（内部边算作两条）
	int tot_edge = (map_weight-1)*(map_height-1) + map_weight * 2 + map_height * 2;
	//随机生成删除边的个数（在60%~80%之间）
	int del_number = getRandomInt(tot_edge/10*6,tot_edge/10*8);

	//DEBUG
	//debug(tem_edge.size())debug(tot_edge)debug(del_number)

	for (int t = 1;t <= del_number;++t)
	{
		// x y style
		tuple<int, int, int> ran_edge = tem_edge[getRandomInt(0, tem_edge.size()-1)];
		bool spj = false;

		//随机抽取，直到找到一条合法的删边
		while(map_wall[get<0>(ran_edge)][get<1>(ran_edge)][get<2>(ran_edge)]==0||checkedge(ran_edge)==0)
		{
			ran_edge = tem_edge[getRandomInt(0, max(0, tem_edge.size() - 1))];
		}

		//DEBUG
		//debug(get<0>(ran_edge))debug(get<1>(ran_edge))debug(get<2>(ran_edge))cout << endl;
		//删除这条边
		map_wall[get<0>(ran_edge)][get<1>(ran_edge)][get<2>(ran_edge)]=0;
		//得到这条边的邻居
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

	//特殊处理，边在相邻点其中一个被删除就算做被删除了
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

	//特殊处理，对于四周均有边的情况，染成深色
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

	//渲染地板
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

	//渲染墙壁
	int tem_wallx, tem_wally;
	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			//DEBUG
			//debug(t)debug(i)debug(map_wall[i][t][0])debug(map_wall[i][t][1])debug(map_wall[i][t][2])debug(map_wall[i][t][3])cout << endl;
			
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

static vector<pair<int,int>> tem_point;
static bool tem_valid[50][50];
void dfsDying(int x, int y)
{
	tem_point.push_back({ x,y });
	tem_valid[x][y] = 1;
	for (int t = 0;t<=3;++t)
	{
		if (map_wall[x][y][t]) continue;
		pair<int, int> tem_neighbor = getNeighbor(x, y, t);
		if (tem_neighbor.first<1 || tem_neighbor.second<1 || tem_neighbor.first>map_weight || tem_neighbor.second>map_height) continue;

		if (!tem_valid[tem_neighbor.first][tem_neighbor.second])
		{
			dfsDying(tem_neighbor.first, tem_neighbor.second);
		}
	}
}
pair<int,int> calcPosition(int x, int y)
{
	pair<int, int> tem_player;
	tem_player.first= (1400 - map_weight * ground_length) / 2 + (x - 1) * ground_length + ground_length / 2;
	tem_player.second = 100 + (y - 1) * ground_length + ground_length / 2;
	return tem_player;
}
bool genSpawn()
{
	tem_point.clear();
	for (int t = 1;t <= map_height;++t)
	{
		for (int i = 1;i <= map_weight;++i)
		{
			tem_valid[i][t] = 0;
		}
	}

	bool spj = false;
	for (int tem_try = 1;tem_try <= 1000;++tem_try)
	{
		pair<int, int> tem_randompos = { getRandomInt(1,map_weight), getRandomInt(1,map_height) };

		for (auto i : tem_point)
		{
			tem_valid[i.first][i.second] = 0;
		}
		tem_point.clear();
		dfsDying(tem_randompos.first, tem_randompos.second);
		if (tem_point.size() < 2) continue;
		spj = 1;
		break;
	}
	if (!spj) return false;

	//一个机智的方法解决在一堆数中抽取两个不同的数
	int tem_u1 = getRandomInt(0, tem_point.size() - 1);
	int tem_u2=(tem_u1+ getRandomInt(1, tem_point.size() - 1))%tem_point.size();
	pair<int, int> tem_player1 = calcPosition(tem_point[tem_u1].first, tem_point[tem_u1].second);
	pair<int,int> tem_player2 = calcPosition(tem_point[tem_u2].first, tem_point[tem_u2].second);

	//DEBUG
	debug(tem_point[tem_u1].first)debug(tem_point[tem_u1].second)debug(tem_point[tem_u2].first)debug(tem_point[tem_u2].second)cout << endl;
	debug(tem_point.size())cout << endl;
	for (auto i : tem_point)
	{
		debug(i.first)debug(i.second)cout << endl;
		debug(map_wall[i.first][i.second][0])debug(map_wall[i.first][i.second][1])debug(map_wall[i.first][i.second][2])debug(map_wall[i.first][i.second][3])cout << endl;
	}

	player1.x = tem_player1.first;
	player1.y = tem_player1.second;
	player2.x = tem_player2.first;
	player2.y = tem_player2.second;
	return true;
}

int initWorld()
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
	genWalls();
	bool tem_result = genSpawn();

	//日志
	if (!tem_result)
	{
		cout << "CRASH#1: THE WORLDGEN PROCESS HAPPENED A RARE EVENT!";
		return 0;
	}
	cout << "Worldgen completed!\n";
	cout << "The details listed below:\n";
	cout << " map_height: " << map_height << '\n';
	cout << "map_weight: " << map_weight << '\n';

	return 1;
}