#include <graphics.h>
#include "fishsouptools.h"
#include "Bullet.h"

Bullet::Bullet(double x, double y, double speed, double r)
{
	this->speed = speed;
	this->r = r;
	pair<double, double> new_xy = calcMovePosition(x, y, r, speed*5);
	this->x = new_xy.first;
	this->y = new_xy.second;
}

int Bullet::update()
{
	//调用工具函数，返回新位置
	pair<double, double> new_xy = calcMovePosition(this->x, this->y, this->r, speed);
	this->x = new_xy.first;
	this->y = new_xy.second;
	if (x < 0 - d || y < 0 - d || x>1400 + d || y>800 + d)
	{
		// 出界返回0
		return 0;
	}
	// 不出界返回1
	return 1;
}

void Bullet::render()
{
	setlinecolor(0xFFFFFF);
	solidcircle(x, y, siz);
}

