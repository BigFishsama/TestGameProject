#pragma once
#include <graphics.h>
#include <list>
#include "Object.h"
#include "Tank.h"
#include "Bullet.h"
using namespace std;

//全局游戏时刻
extern int time_tick;

//声明实体渲染列表与背景渲染列表
extern list<FishSoup_Object*> render_list;
extern list<FishSoup_Object*> background_object;

//声明玩家
extern Tank player1;
extern Tank player2;

//地图信息
extern int map_weight, map_height,ground_length;
extern int map_corner1_x, map_corner1_y;
extern int map_corner2_x, map_corner2_y;
extern int map[1405][805];
extern int map_ground[50][50];
extern bool map_wall[50][50][4];

//全局缩放等级
extern double scalelevel;


class Manager
{
public:
	// 初始化游戏信息
	void init();
	void initbackground();

	// 处理信息，更新游戏
	void update();

	// 渲染游戏
	void renderAllObeject();
};
//声明游戏控制台
extern Manager manager;
