#include "Manager.h"
#include "fishsouptools.h"
#include <graphics.h>
#include <list>
#include <iostream>
#include "Ground.h"
#include "Worldgen.h"
using namespace std;

//在单一文件中定义全局数据
// 
//此处重大BUG!!!!!
//原定义list<FishSoup_Obeject> render_list;
//会丢失子类信息，发生对象切片，需要改为存储地址
list<FishSoup_Object*> render_list;

//静态背景
list<FishSoup_Object*> background_object;
IMAGE background_img;

Tank player(400, 300, 0, 'W', 'S', 'A', 'D', 'R');
Bullet player_Bullet(0, 0, 0, 0);
Manager manager;

int map_height, map_weight;
bool map[1400][800];
int map_ground[50][50];
bool map_wall[50][50][4];
int ground_length;

double scalelevel=1;

//初始化游戏
void Manager::init()
{
	//上下留空100，故最大为1400*600
	initgraph(1400, 800);
	
	initWorld();
	initbackground();
	player.update_model();
	render_list.push_back(&player);
}

//绘制并保存背景
void Manager::initbackground()
{
	background_img = IMAGE(1400, 800);
	SetWorkingImage(&background_img);
	for(auto it=background_object.begin();it!=background_object.end();++it)
	{
		(*it)->render();
	}
	SetWorkingImage();
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
	putimage(0, 0, &background_img);
	for (auto it = render_list.begin();it != render_list.end();++it)
	{
		(*it)->render();
	}
}
