#include <graphics.h>
#include <iostream>
#include "Tank.h"
#include "Bullet.h"
#include "fishsouptools.h"
#include "Manager.h"

void Tank::initrender()
{
	loadimage(&(this->Texture), L"image/Tanks/Tank.png", 100, 100, true);
	loadimage(&(this->printed_Texture), L"image/Tanks/Tank.png", 100, 100, true);
}
Tank::Tank(double x,double y,double r)
{
	this->initrender();
	this->x = x;
	this->y = y;
	this->r = r;
}
Tank::Tank(double x, double y, double r, char key_up, char key_down, char key_left, char key_right, char key_shoot)
{
	this->initrender();
	this->x = x;
	this->y = y;
	this->r = r;
	this->key_up = key_up;
	this->key_down = key_down;
	this->key_left = key_left;
	this->key_right = key_right;
	this->key_shoot = key_shoot;
}

// 向方向上移动dis个单位长度
void Tank::move(double dis)
{
	//调用工具函数，返回新位置
	pair<int, int> new_xy = calcMovePosition(this->x, this->y, this->r, dis);
	this->x = new_xy.first;
	this->y = new_xy.second;
}

// 旋转radius度，顺时针
void Tank::turn(double radius)
{
	r += PI / 180 * radius;
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
	if (GetAsyncKeyState('A') & 0x8000)
	{
		this->turn(2);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		this->turn(-2);
	}
	if (GetAsyncKeyState('W') & 0x8000)
	{
		this->move(3);
	}
	if (GetAsyncKeyState('S') & 0x8000)
	{
		this->move(-3);
	}
	if (GetAsyncKeyState('R') & 0x8000)
	{
		if (this->cd_shoot == 0)
		{
			this->cd_shoot = 40;
			this->shoot();
		}
	}
	if (this->cd_shoot) --this->cd_shoot;
	//玩家不出界，不删除，返回1
	return 1;
}