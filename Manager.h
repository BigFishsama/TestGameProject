#pragma once
#include <graphics.h>
#include <list>
#include "Object.h"
#include "Tank.h"
#include "Bullet.h"
using namespace std;

//声明实体渲染列表
extern list<FishSoup_Obeject*> render_list;

//声明玩家1
extern Tank player;
extern Bullet player_Bullet;

//地图信息
extern int map_weight, map_height,ground_length;

//全局缩放等级
extern double scalelevel;


class Manager
{
public:
	// 初始化游戏信息
	void init();

	// 处理信息，更新游戏
	void update();

	// 渲染游戏
	void renderAllObeject();
};
//声明游戏控制台
extern Manager manager;
