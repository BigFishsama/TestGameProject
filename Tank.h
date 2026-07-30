#pragma once
#include <graphics.h>
#include <cmath>
#include "Object.h"
#include "fishsouptools.h"
#include <iostream>
using namespace std;
class Tank:public FishSoup_Object {
public:
	int cd_shoot = 100;
	vector<pair<int, int> > hitbox;
	COLORREF color;

	//默认朝向右边
	int default_height=30, default_weight=40;
	double height, weight;
	double tem_length;
	double default_movespeed=1, default_turnspeed=1;
	double movespeed, turnspeed;

	//底座四个点从左上角顺时针到左下角
	double r1,r2,r3,r4;
	pair<int, int> tem_point1, tem_point2, tem_point3, tem_point4;
	
	int controlmode;
	Tank(double x, double y, double r);
	Tank(double x, double y, double r,int controlmode);
	virtual void render() override;
	virtual void move(double dis);
	virtual void turn(double radius);

	virtual void shoot();
	virtual int update() override;

	virtual void update_model();
	virtual void getHitbox(double tem_x, double tem_y, double tem_r, vector<pair<int, int>>& tem_pixels);
	virtual bool checkHitbox(double tem_x, double tem_y, double tem_r);
	virtual void update_hitbox();
};