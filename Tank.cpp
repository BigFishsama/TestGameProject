#include <graphics.h>
#include <iostream>
#include "Tank.h"
#include "Bullet.h"
#include "fishsouptools.h"
#include "Manager.h"

Tank::Tank(double x,double y,double r)
{
	this->x = x;
	this->y = y;
	this->r = r;
	update_model();
}
Tank::Tank(double x, double y, double r,int controlmode)
{
	this->controlmode = controlmode;
	if (controlmode == 1)
	{
		this->color = RGB(150, 70, 60);
	}
	else
	{
		this->color = RGB(60, 75, 45);
	}
	Tank(x, y, r);
}
void Tank::update_model()
{
	//日志
	cout << "model has been updated successfully!\n";
	cout << "The scalelevel is " << scalelevel<<'\n';

	this->height = default_height / scalelevel;
	this->weight = default_weight / scalelevel;
	this->movespeed = default_movespeed / scalelevel;
	this->turnspeed = default_turnspeed;
	tem_length = (double)sqrt((height / 2.0) * (height / 2.0) + (weight / 2.0) * (weight / 2.0));
	//底座四个点从左上角顺时针到左下角
	r1 = atan2(-height, -weight);
	r2 = atan2(-height, weight);
	r3 = atan2(height, weight);
	r4 = atan2(height, -weight);
}

// 向方向上移动dis个单位长度
void Tank::move(double dis)
{
	//调用工具函数，返回新位置
	pair<double, double> new_xy = calcMovePosition(this->x, this->y, this->r, dis);
	if (checkHitbox(new_xy.first, y, this->r))
	{
		this->x = new_xy.first;
	}
	if (checkHitbox(x,new_xy.second, this->r))
	{
		this->y = new_xy.second;
	}
	//else cout << "DEBUG#1: Fail to MOVE due to Hitbox\n";
}


// 旋转radius弧度，顺时针方向为正，0度是x轴向右
//1°约为0.01745
void Tank::turn(double radius)
{
	double tem_r = this->r + radius * 0.01745;
	if (checkHitbox(this->x, this->y, tem_r))
	{
		this->r = tem_r;
	}
	//else cout << "DEBUG#2: Fail to TURN due to Hitbox\n";
}

// 发射子弹
void Tank::shoot()
{
	double x = this->x, y = this->y, r = this->r, speed = 5;
	Bullet* tem_Bullet=new Bullet(x, y, speed, r);

	render_list.push_back(tem_Bullet);
}

// 处理按键信息
int Tank::update()
{
	//cout <<"Tank has been updated successfully !!!";
	int input_move=0, input_turn = 0;
	bool input_shoot = false;
	if (controlmode == 1)
	{
		if (GetAsyncKeyState('A') & 0x8000) input_turn -= 1;
		if (GetAsyncKeyState('D') & 0x8000) input_turn += 1;
		if (GetAsyncKeyState('W') & 0x8000) input_move += 1;
		if (GetAsyncKeyState('S') & 0x8000) input_move -= 1;
		if (GetAsyncKeyState('R') & 0x8000)
		{
			if (this->cd_shoot == 0)
			{
				input_shoot = 1;
			}
		}
	}
	else
	{
		if (GetAsyncKeyState(VK_LEFT) & 0x8000) input_turn -= 1;
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000) input_turn += 1;
		if (GetAsyncKeyState(VK_UP) & 0x8000) input_move += 1;
		if (GetAsyncKeyState(VK_DOWN) & 0x8000) input_move -= 1;
		if (GetAsyncKeyState('R') & 0x8000)
		{
			if (this->cd_shoot == 0)
			{
				input_shoot = 1;
			}
		}
	}
	if (input_move != 0)
	{
		this->move(movespeed * input_move);
		//if (!checkHitbox(x, y, r))
		//{
		//	cout << "CRASH#3 HitBox Error.Moving!\n";
		//}
	}
	if (input_turn != 0)
	{
		this->turn(turnspeed * input_turn);
		//if (!checkHitbox(x, y, r))
		//{
		//	cout << "CRASH#4 HitBox Error.Turing!\n";
		//}
	}
	if (input_shoot)
	{
		this->cd_shoot = 41;
		this->shoot();
	}
	if (this->cd_shoot) --this->cd_shoot;
	//玩家永远不出界，不删除，返回1
	return 1;
}

void Tank::getHitbox(double tem_x, double tem_y, double tem_r, vector<pair<int, int>>& tem_pixels)
{
	tem_point1 = calcMovePosition(tem_x, tem_y, r1 + tem_r, tem_length);
	tem_point2 = calcMovePosition(tem_x, tem_y, r2 + tem_r, tem_length);
	tem_point3 = calcMovePosition(tem_x, tem_y, r3 + tem_r, tem_length);
	tem_point4 = calcMovePosition(tem_x, tem_y, r4 + tem_r, tem_length);
	getLinepixel(tem_point1.first, tem_point1.second, tem_point2.first, tem_point2.second,tem_pixels);
	getLinepixel(tem_point2.first, tem_point2.second, tem_point3.first, tem_point3.second, tem_pixels);
	getLinepixel(tem_point3.first, tem_point3.second, tem_point4.first, tem_point4.second, tem_pixels);
	getLinepixel(tem_point4.first, tem_point4.second, tem_point1.first, tem_point1.second, tem_pixels);
}
bool Tank::checkHitbox(double tem_x, double tem_y, double tem_r)
{
	vector<pair<int, int>> tem_pixels = {};
	getHitbox(tem_x, tem_y, tem_r, tem_pixels);

	//DEBUG
	//debug(tem_pixels.size())
	for (auto i : tem_pixels)
	{
		//cout << i.first << ' ' << i.second << '\n';
		if (map[(int)i.first][(int)i.second])
		{
			//cout << "Find!";
			return false;
		}
	}
	return true;
}

void Tank::render()
{
	setfillcolor(color);

	//绘制底座
	update_hitbox();
	POINT tem_points[] = { {tem_point1.first,tem_point1.second},{tem_point2.first,tem_point2.second} ,{tem_point3.first,tem_point3.second},{tem_point4.first,tem_point4.second} };
	
	solidpolygon(tem_points, 4);

	//line(tem_point1.first, tem_point1.second, tem_point2.first, tem_point2.second);
	//line(tem_point2.first, tem_point2.second, tem_point3.first, tem_point3.second);
	//line(tem_point3.first, tem_point3.second, tem_point4.first, tem_point4.second);
	//line(tem_point4.first, tem_point4.second, tem_point1.first, tem_point1.second);
}

void Tank::update_hitbox()
{
	tem_point1 = calcMovePosition(x, y, r1 + r, tem_length);
	tem_point2 = calcMovePosition(x, y, r2 + r, tem_length);
	tem_point3 = calcMovePosition(x, y, r3 + r, tem_length);
	tem_point4 = calcMovePosition(x, y, r4 + r, tem_length);
	////清空之前碰撞箱信息
	//for (auto i : hitbox)
	//{

	//}
}