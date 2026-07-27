#include <graphics.h>
#include "fishsouptools.h"
#include "Bullet.h"


void Bullet::initrender()
{
	loadimage(&(this->Texture), L"image/Bullets/bullet.png", 20, 34, true);
	loadimage(&(this->printed_Texture), L"image/Bullets/bullet.png", 20, 34, true);
}

Bullet::Bullet(double x, double y, double speed, double r)
{
	//初始化贴图
	this->initrender();

	this->x = x - speed * 10 * sin(r);
	this->y = y - speed * 10 * cos(r);
	this->speed = speed;
	this->r = r;
}

int Bullet::update()
{
	double dx = speed * sin(r);
	double dy = speed * cos(r);
	x -= dx;
	y -= dy;
	if (x < 0 - d || y < 0 - d || x>800 + d || y>600 + d)
	{
		// 出界返回0
		return 0;
	}
	// 不出界返回1
	return 1;
}

