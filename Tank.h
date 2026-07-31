#pragma once
#include <graphics.h>
#include <cmath>
#include "Object.h"
#include "fishsouptools.h"
#include <iostream>
using namespace std;
class Tank:public FishSoup_Object {
public:
	vector<pair<int, int> > hitbox;

	//底座信息
	double r1, r2, r3, r4;
	pair<int, int> point1, point2, point3, point4;
	double base_length;

	//车身信息
	int default_body_left_height = 7, default_body_left_weight = 15;
	int default_body_right_height = 7, default_body_right_weight = 10;
	double body_left_height, body_left_weight;
	double body_right_height, body_right_weight;
	double body_length1, body_length2, body_length3, body_length4;
	double r5, r6, r7, r8;
	pair<int, int> point5, point6, point7, point8;
	COLORREF body_color = RGB(94, 177, 94);
	//COLORREF body_outline_color = RGB(73,126,73);
	

	//履带信息
	COLORREF track_outline_color = RGB(46,43,34);
	COLORREF track_color = RGB(64, 60, 47);
	
	//炮台信息
	int default_turret_left_height = 5, default_turret_left_weight = 4;
	int default_turret_right_height = 5, default_turret_right_weight = 7;
	double turret_left_height, turret_left_weight;
	double turret_right_height, turret_right_weight;
	double turret_length1, turret_length2, turret_length3, turret_length4;
	double r13, r14, r15, r16;
	pair<int, int> point13, point14, point15, point16;
	COLORREF turret_color = RGB(90, 156, 90);

	//炮筒信息
	int default_barrel_left_height = 3, default_barrel_left_weight = 1;
	int default_barrel_right_height = 3, default_barrel_right_weight = 18;
	double barrel_left_height, barrel_left_weight;
	double barrel_right_height, barrel_right_weight;
	double barrel_length1, barrel_length2, barrel_length3, barrel_length4;
	double r17, r18, r19, r20;
	pair<int, int> point17, point18, point19, point20;
	COLORREF barrel_outline_color = RGB(73, 126, 73);
	COLORREF barrel_color= RGB(81, 145, 81);

	//后侧信息
	int default_back_left_height = 4, default_back_left_weight = 15;
	int default_back_right_height = 4, default_back_right_weight = 11;
	double back_left_height, back_left_weight;
	double back_right_height, back_right_weight;
	double back_length1, back_length2, back_length3, back_length4;
	double r9, r10, r11, r12;
	pair<int, int> point9, point10, point11, point12;
	COLORREF back_color = RGB(90, 156, 90);

	//坦克基础信息（默认朝向右方）,碰撞箱信息
	int default_height=30, default_weight=30;
	double height, weight;

	//注意如果修改炮筒和底座信息，此处也要更改
	int default_d_height = 3, default_d_weight = 15;
	double d_height, d_weight;
	double d_length1, d_length2;
	double r21, r22;
	pair<int, int> point21, point22;

	double default_movespeed=1.5, default_turnspeed=1.5;
	double movespeed, turnspeed;
	int cd_shoot = 100;
	
	//控制模式
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