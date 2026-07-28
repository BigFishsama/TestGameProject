#include "Manager.h"
#include "fishsouptools.h"
#include <graphics.h>
#include <list>
#include <iostream>
#include "Ground.h"
using namespace std;

//在单一文件中定义全局数据
// 
//此处重大BUG!!!!!
//原定义list<FishSoup_Obeject> render_list;
//会丢失子类信息，发生对象切片，需要改为存储地址
list<FishSoup_Obeject*> render_list;
Tank player(400, 300, 0, 'W', 'S', 'A', 'D', 'R');
Bullet player_Bullet(0, 0, 0, 0);
Manager manager;
int map_height, map_weight;
int ground_length;
double scalelevel=1;

void Manager::init()
{
	//上下留空100，故最大为1400*600
	initgraph(1400, 800);
	
	//纵轴可选的方块个数
	int tem_ground_length[7] = { 2,3,5,6,8,10,12 };
	map_height = tem_ground_length[getRandomInt(0, 6)];

	//得到单个地板的边长
	ground_length = 600 / map_height;

	//计算相对于100的缩放等级
	scalelevel = 100.0 / ground_length;

	//此处不想横轴填满所以缩小了100
	int tem_ceil = 1300 / ground_length;
	map_weight = getRandomInt(min(tem_ceil,5), tem_ceil);

	for (int t = 0,sty=100;t < map_height;++t)
	{
		for (int i = 0,stx=(1400-map_weight*ground_length)/2;i < map_weight;++i)
		{
			Ground* u = new Ground(stx+i* ground_length,sty+t* ground_length, ground_length);
			render_list.push_back(u);
		}
	}
	player.update_model();
	render_list.push_back(&player);
}
void Manager::update()
{
	//cout << render_list.size();
	for (auto it = render_list.begin();it != render_list.end();)
	{
		int re = (*it)->update();
		if (!re)
		{
			//释放内存
			delete *it;
			it = render_list.erase(it);
			continue;
		}
		++it;
	}
}
void Manager::renderAllObeject()
{
	for (auto it = render_list.begin();it != render_list.end();++it)
	{
		(*it)->render();
	}
}
