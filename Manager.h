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
