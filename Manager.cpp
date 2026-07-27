#include "Manager.h"
#include "fishsouptools.h"
#include <graphics.h>
#include <list>
#include <iostream>
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


void Manager::init()
{
	initgraph(800, 600);
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
