#pragma once
#include <graphics.h>
#include <cmath>
#include "Object.h"
#include "fishsouptools.h"
#include <iostream>
using namespace std;
class Tank:public FishSoup_Obeject {
public:
	int cd_shoot = 100;

	//默认朝向右边
	int default_height=30, default_weight=40;
	double height, weight;
	double tem_length;

	//底座四个点从左上角顺时针到左下角
	double r1,r2,r3,r4;
	
	char key_up, key_down, key_left, key_right, key_shoot;
	Tank(double x, double y, double r);
	Tank(double x, double y, double r, char key_up, char key_down, char key_left, char key_right, char key_shoot);
	virtual void render() override;
	virtual void move(double dis);
	virtual void turn(double radius);
	virtual void shoot();
	virtual int update() override;

	virtual void update_model();
};