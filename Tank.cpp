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
Tank::Tank(double x, double y, double r, char key_up, char key_down, char key_left, char key_right, char key_shoot)
{
	this->key_up = key_up;
	this->key_down = key_down;
	this->key_left = key_left;
	this->key_right = key_right;
	this->key_shoot = key_shoot;
	Tank(x, y, r);
}
void Tank::update_model()
{
	cout << "model has been updated successfully!\n";
	cout << "The scalelevel is " << scalelevel<<'\n';
	this->height = default_height / scalelevel;
	this->weight = default_weight / scalelevel;
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
	this->x = new_xy.first;
	this->y = new_xy.second;
}

// 旋转radius度，顺时针方向为正，0度是x轴向右
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
		this->turn(-2);
	}
	if (GetAsyncKeyState('D') & 0x8000)
	{
		this->turn(2);
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

void Tank::render()
{
	setlinecolor(0xFFFFFF);
	//绘制底座
	pair<double, double> tem_point1, tem_point2, tem_point3, tem_point4;
	tem_point1 = calcMovePosition(x, y, r1 + r, tem_length);
	tem_point2 = calcMovePosition(x, y, r2 + r, tem_length);
	tem_point3 = calcMovePosition(x, y, r3 + r, tem_length);
	tem_point4 = calcMovePosition(x, y, r4 + r, tem_length);
	line(tem_point1.first, tem_point1.second, tem_point2.first, tem_point2.second);
	line(tem_point2.first, tem_point2.second, tem_point3.first, tem_point3.second);
	line(tem_point3.first, tem_point3.second, tem_point4.first, tem_point4.second);
	line(tem_point4.first, tem_point4.second, tem_point1.first, tem_point1.second);
}